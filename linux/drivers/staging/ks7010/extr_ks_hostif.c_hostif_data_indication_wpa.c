#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wrqu ;
struct TYPE_6__ {int /*<<< orphan*/  length; } ;
union iwreq_data {TYPE_3__ data; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct wpa_key {int /*<<< orphan*/  rx_mic_key; scalar_t__ key_len; } ;
struct mic_failure {unsigned long last_failure_time; int failure; int counter; } ;
struct TYPE_5__ {scalar_t__ pairwise_suite; scalar_t__ group_suite; struct mic_failure mic_failure; struct wpa_key* key; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_errors; } ;
struct ks_wlan_private {int rxp; int rx_size; int /*<<< orphan*/  net_dev; TYPE_2__ wpa; TYPE_1__ nstats; } ;
struct ether_hdr {scalar_t__ h_dest_snap; scalar_t__ h_source_snap; int* h_dest; int /*<<< orphan*/  h_source; int /*<<< orphan*/  h_proto; } ;
typedef  int /*<<< orphan*/  recv_mic ;
typedef  int /*<<< orphan*/  mic ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  IWEVCUSTOM ; 
 scalar_t__ IW_AUTH_CIPHER_TKIP ; 
 int MICHAEL_MIC_LEN ; 
 unsigned short TYPE_GMK1 ; 
 unsigned short TYPE_GMK2 ; 
 unsigned short TYPE_PMK1 ; 
 unsigned long jiffies ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int,int) ; 
 int /*<<< orphan*/  memset (union iwreq_data*,int /*<<< orphan*/ ,int) ; 
 int michael_mic (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,unsigned short,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned short ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  wireless_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union iwreq_data*,char*) ; 

__attribute__((used)) static
int hostif_data_indication_wpa(struct ks_wlan_private *priv,
			       unsigned short auth_type)
{
	struct ether_hdr *eth_hdr;
	unsigned short eth_proto;
	unsigned char recv_mic[MICHAEL_MIC_LEN];
	char buf[128];
	unsigned long now;
	struct mic_failure *mic_failure;
	u8 mic[MICHAEL_MIC_LEN];
	union iwreq_data wrqu;
	unsigned int key_index = auth_type - 1;
	struct wpa_key *key = &priv->wpa.key[key_index];

	eth_hdr = (struct ether_hdr *)(priv->rxp);
	eth_proto = ntohs(eth_hdr->h_proto);

	if (eth_hdr->h_dest_snap != eth_hdr->h_source_snap) {
		netdev_err(priv->net_dev, "invalid data format\n");
		priv->nstats.rx_errors++;
		return -EINVAL;
	}
	if (((auth_type == TYPE_PMK1 &&
	      priv->wpa.pairwise_suite == IW_AUTH_CIPHER_TKIP) ||
	     (auth_type == TYPE_GMK1 &&
	      priv->wpa.group_suite == IW_AUTH_CIPHER_TKIP) ||
	     (auth_type == TYPE_GMK2 &&
	      priv->wpa.group_suite == IW_AUTH_CIPHER_TKIP)) &&
	    key->key_len) {
		int ret;

		netdev_dbg(priv->net_dev, "TKIP: protocol=%04X: size=%u\n",
			   eth_proto, priv->rx_size);
		/* MIC save */
		memcpy(&recv_mic[0],
		       (priv->rxp) + ((priv->rx_size) - sizeof(recv_mic)),
		       sizeof(recv_mic));
		priv->rx_size = priv->rx_size - sizeof(recv_mic);

		ret = michael_mic(key->rx_mic_key, priv->rxp, priv->rx_size,
				  0, mic);
		if (ret < 0)
			return ret;
		if (memcmp(mic, recv_mic, sizeof(mic)) != 0) {
			now = jiffies;
			mic_failure = &priv->wpa.mic_failure;
			/* MIC FAILURE */
			if (mic_failure->last_failure_time &&
			    (now - mic_failure->last_failure_time) / HZ >= 60) {
				mic_failure->failure = 0;
			}
			netdev_err(priv->net_dev, "MIC FAILURE\n");
			if (mic_failure->failure == 0) {
				mic_failure->failure = 1;
				mic_failure->counter = 0;
			} else if (mic_failure->failure == 1) {
				mic_failure->failure = 2;
				mic_failure->counter =
					(u16)((now - mic_failure->last_failure_time) / HZ);
				/*  range 1-60 */
				if (!mic_failure->counter)
					mic_failure->counter = 1;
			}
			priv->wpa.mic_failure.last_failure_time = now;

			/*  needed parameters: count, keyid, key type, TSC */
			sprintf(buf,
				"MLME-MICHAELMICFAILURE.indication(keyid=%d %scast addr=%pM)",
				key_index,
				eth_hdr->h_dest[0] & 0x01 ? "broad" : "uni",
				eth_hdr->h_source);
			memset(&wrqu, 0, sizeof(wrqu));
			wrqu.data.length = strlen(buf);
			wireless_send_event(priv->net_dev, IWEVCUSTOM, &wrqu,
					    buf);
			return -EINVAL;
		}
	}
	return 0;
}