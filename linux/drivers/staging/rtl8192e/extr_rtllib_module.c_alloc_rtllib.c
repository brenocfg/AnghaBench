#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sw_cam_table {int dummy; } ;
struct rtllib_device {int open_wep; int host_encrypt; int host_decrypt; int ieee802_1x; int* last_rxseq_num; int* last_rxfrag_num; scalar_t__* last_packet_time; int /*<<< orphan*/ * ibss_mac_hash; int /*<<< orphan*/  pHTInfo; int /*<<< orphan*/  swcamtable; scalar_t__ hwsec_active; scalar_t__ raw_tx; scalar_t__ privacy_invoked; scalar_t__ drop_unencrypted; scalar_t__ tkip_countermeasures; scalar_t__ wpa_enabled; int /*<<< orphan*/  lock; int /*<<< orphan*/  crypt_info; int /*<<< orphan*/  atm_swbw; int /*<<< orphan*/  reorder_spinlock; int /*<<< orphan*/  wpax_suitlist_lock; int /*<<< orphan*/  rtllib_ap_sec_type; int /*<<< orphan*/  scan_age; int /*<<< orphan*/  fts; struct net_device* dev; } ;
struct rt_hi_throughput {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_FTS ; 
 int /*<<< orphan*/  DEFAULT_MAX_SCAN_AGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HTInitializeHTInfo (struct rtllib_device*) ; 
 int /*<<< orphan*/  HTUpdateDefaultSetting (struct rtllib_device*) ; 
 int IEEE_IBSS_MAC_HASH_SIZE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TSInitialize (struct rtllib_device*) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lib80211_crypt_info_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ netdev_priv_rsl (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  rtllib_ap_sec_type ; 
 int rtllib_networks_allocate (struct rtllib_device*) ; 
 int /*<<< orphan*/  rtllib_networks_initialize (struct rtllib_device*) ; 
 int /*<<< orphan*/  rtllib_softmac_init (struct rtllib_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct net_device *alloc_rtllib(int sizeof_priv)
{
	struct rtllib_device *ieee = NULL;
	struct net_device *dev;
	int i, err;

	pr_debug("rtllib: Initializing...\n");

	dev = alloc_etherdev(sizeof(struct rtllib_device) + sizeof_priv);
	if (!dev) {
		pr_err("Unable to allocate net_device.\n");
		return NULL;
	}
	ieee = (struct rtllib_device *)netdev_priv_rsl(dev);
	ieee->dev = dev;

	err = rtllib_networks_allocate(ieee);
	if (err) {
		pr_err("Unable to allocate beacon storage: %d\n", err);
		goto failed;
	}
	rtllib_networks_initialize(ieee);

	/* Default fragmentation threshold is maximum payload size */
	ieee->fts = DEFAULT_FTS;
	ieee->scan_age = DEFAULT_MAX_SCAN_AGE;
	ieee->open_wep = 1;

	/* Default to enabling full open WEP with host based encrypt/decrypt */
	ieee->host_encrypt = 1;
	ieee->host_decrypt = 1;
	ieee->ieee802_1x = 1; /* Default to supporting 802.1x */

	ieee->rtllib_ap_sec_type = rtllib_ap_sec_type;

	spin_lock_init(&ieee->lock);
	spin_lock_init(&ieee->wpax_suitlist_lock);
	spin_lock_init(&ieee->reorder_spinlock);
	atomic_set(&(ieee->atm_swbw), 0);

	/* SAM FIXME */
	lib80211_crypt_info_init(&ieee->crypt_info, "RTLLIB", &ieee->lock);

	ieee->wpa_enabled = 0;
	ieee->tkip_countermeasures = 0;
	ieee->drop_unencrypted = 0;
	ieee->privacy_invoked = 0;
	ieee->ieee802_1x = 1;
	ieee->raw_tx = 0;
	ieee->hwsec_active = 0;

	memset(ieee->swcamtable, 0, sizeof(struct sw_cam_table) * 32);
	rtllib_softmac_init(ieee);

	ieee->pHTInfo = kzalloc(sizeof(struct rt_hi_throughput), GFP_KERNEL);
	if (!ieee->pHTInfo)
		return NULL;

	HTUpdateDefaultSetting(ieee);
	HTInitializeHTInfo(ieee);
	TSInitialize(ieee);
	for (i = 0; i < IEEE_IBSS_MAC_HASH_SIZE; i++)
		INIT_LIST_HEAD(&ieee->ibss_mac_hash[i]);

	for (i = 0; i < 17; i++) {
		ieee->last_rxseq_num[i] = -1;
		ieee->last_rxfrag_num[i] = -1;
		ieee->last_packet_time[i] = 0;
	}

	return dev;

 failed:
	free_netdev(dev);
	return NULL;
}