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
struct net_device {int dummy; } ;
struct ieee80211_device {int open_wep; int host_encrypt; int host_decrypt; int ieee802_1x; int* last_rxseq_num; int* last_rxfrag_num; scalar_t__* last_packet_time; int /*<<< orphan*/ * ibss_mac_hash; int /*<<< orphan*/  pHTInfo; scalar_t__ hwsec_active; scalar_t__ raw_tx; scalar_t__ privacy_invoked; scalar_t__ drop_unencrypted; scalar_t__ tkip_countermeasures; scalar_t__ wpa_enabled; scalar_t__ wpax_type_set; int /*<<< orphan*/  atm_swbw; int /*<<< orphan*/  atm_chnlop; int /*<<< orphan*/  reorder_spinlock; int /*<<< orphan*/  bw_spinlock; int /*<<< orphan*/  wpax_suitlist_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  crypt_deinit_timer; int /*<<< orphan*/  crypt_deinit_list; int /*<<< orphan*/  scan_age; int /*<<< orphan*/  fts; struct net_device* dev; } ;
typedef  int /*<<< orphan*/  RT_HIGH_THROUGHPUT ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_FTS ; 
 int /*<<< orphan*/  DEFAULT_MAX_SCAN_AGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HTInitializeHTInfo (struct ieee80211_device*) ; 
 int /*<<< orphan*/  HTUpdateDefaultSetting (struct ieee80211_device*) ; 
 int /*<<< orphan*/  IEEE80211_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IEEE80211_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  IEEE80211_DL_ERR ; 
 int /*<<< orphan*/  IEEE80211_ERROR (char*,...) ; 
 int IEEE_IBSS_MAC_HASH_SIZE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TSInitialize (struct ieee80211_device*) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  ieee80211_crypt_deinit_handler ; 
 int ieee80211_networks_allocate (struct ieee80211_device*) ; 
 int /*<<< orphan*/  ieee80211_networks_free (struct ieee80211_device*) ; 
 int /*<<< orphan*/  ieee80211_networks_initialize (struct ieee80211_device*) ; 
 int /*<<< orphan*/  ieee80211_softmac_init (struct ieee80211_device*) ; 
 int /*<<< orphan*/  ieee80211_tkip_null () ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 struct ieee80211_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct net_device *alloc_ieee80211(int sizeof_priv)
{
	struct ieee80211_device *ieee;
	struct net_device *dev;
	int i, err;

	IEEE80211_DEBUG_INFO("Initializing...\n");

	dev = alloc_etherdev(sizeof(struct ieee80211_device) + sizeof_priv);
	if (!dev) {
		IEEE80211_ERROR("Unable to network device.\n");
		goto failed;
	}

	ieee = netdev_priv(dev);
	ieee->dev = dev;

	err = ieee80211_networks_allocate(ieee);
	if (err) {
		IEEE80211_ERROR("Unable to allocate beacon storage: %d\n",
				err);
		goto failed;
	}
	ieee80211_networks_initialize(ieee);

	/* Default fragmentation threshold is maximum payload size */
	ieee->fts = DEFAULT_FTS;
	ieee->scan_age = DEFAULT_MAX_SCAN_AGE;
	ieee->open_wep = 1;

	/* Default to enabling full open WEP with host based encrypt/decrypt */
	ieee->host_encrypt = 1;
	ieee->host_decrypt = 1;
	ieee->ieee802_1x = 1; /* Default to supporting 802.1x */

	INIT_LIST_HEAD(&ieee->crypt_deinit_list);
	timer_setup(&ieee->crypt_deinit_timer, ieee80211_crypt_deinit_handler,
		    0);

	spin_lock_init(&ieee->lock);
	spin_lock_init(&ieee->wpax_suitlist_lock);
	spin_lock_init(&ieee->bw_spinlock);
	spin_lock_init(&ieee->reorder_spinlock);
	/* added by WB */
	atomic_set(&ieee->atm_chnlop, 0);
	atomic_set(&ieee->atm_swbw, 0);

	ieee->wpax_type_set = 0;
	ieee->wpa_enabled = 0;
	ieee->tkip_countermeasures = 0;
	ieee->drop_unencrypted = 0;
	ieee->privacy_invoked = 0;
	ieee->ieee802_1x = 1;
	ieee->raw_tx = 0;
	//ieee->hwsec_support = 1; //defalt support hw security. //use module_param instead.
	ieee->hwsec_active = 0; /* disable hwsec, switch it on when necessary. */

	ieee80211_softmac_init(ieee);

	ieee->pHTInfo = kzalloc(sizeof(RT_HIGH_THROUGHPUT), GFP_KERNEL);
	if (!ieee->pHTInfo) {
		IEEE80211_DEBUG(IEEE80211_DL_ERR, "can't alloc memory for HTInfo\n");

		/* By this point in code ieee80211_networks_allocate() has been
		 * successfully called so the memory allocated should be freed
		 */
		ieee80211_networks_free(ieee);
		goto failed;
	}
	HTUpdateDefaultSetting(ieee);
	HTInitializeHTInfo(ieee); /* may move to other place. */
	TSInitialize(ieee);

	for (i = 0; i < IEEE_IBSS_MAC_HASH_SIZE; i++)
		INIT_LIST_HEAD(&ieee->ibss_mac_hash[i]);

	for (i = 0; i < 17; i++) {
		ieee->last_rxseq_num[i] = -1;
		ieee->last_rxfrag_num[i] = -1;
		ieee->last_packet_time[i] = 0;
	}

/* These function were added to load crypte module autoly */
	ieee80211_tkip_null();

	return dev;

 failed:
	if (dev)
		free_netdev(dev);

	return NULL;
}