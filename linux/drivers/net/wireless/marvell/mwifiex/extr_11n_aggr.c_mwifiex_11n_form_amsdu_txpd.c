#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct txpd {scalar_t__ tx_control; int /*<<< orphan*/  flags; void* tx_pkt_length; void* tx_pkt_type; void* tx_pkt_offset; int /*<<< orphan*/  bss_type; int /*<<< orphan*/  bss_num; int /*<<< orphan*/  pkt_delay_2ms; scalar_t__ priority; } ;
struct sk_buff {int len; scalar_t__ priority; scalar_t__ data; } ;
struct mwifiex_txinfo {int flags; } ;
struct mwifiex_private {TYPE_1__* adapter; int /*<<< orphan*/  pkt_tx_ctrl; int /*<<< orphan*/  bss_type; int /*<<< orphan*/  bss_num; } ;
struct TYPE_2__ {int tx_lock_flag; scalar_t__ pps_uapsd_mode; } ;

/* Variables and functions */
 scalar_t__ GET_BSS_ROLE (struct mwifiex_private*) ; 
 scalar_t__ MWIFIEX_BSS_ROLE_STA ; 
 int MWIFIEX_BUF_FLAG_TDLS_PKT ; 
 struct mwifiex_txinfo* MWIFIEX_SKB_TXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  MWIFIEX_TXPD_FLAGS_TDLS_PACKET ; 
 int /*<<< orphan*/  MWIFIEX_TxPD_POWER_MGMT_LAST_PACKET ; 
 int PKT_TYPE_AMSDU ; 
 void* cpu_to_le16 (int) ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct txpd*,int /*<<< orphan*/ ,int) ; 
 int mwifiex_check_last_packet_indication (struct mwifiex_private*) ; 
 int /*<<< orphan*/  mwifiex_wmm_compute_drv_pkt_delay (struct mwifiex_private*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static void
mwifiex_11n_form_amsdu_txpd(struct mwifiex_private *priv,
			    struct sk_buff *skb)
{
	struct txpd *local_tx_pd;
	struct mwifiex_txinfo *tx_info = MWIFIEX_SKB_TXCB(skb);

	skb_push(skb, sizeof(*local_tx_pd));

	local_tx_pd = (struct txpd *) skb->data;
	memset(local_tx_pd, 0, sizeof(struct txpd));

	/* Original priority has been overwritten */
	local_tx_pd->priority = (u8) skb->priority;
	local_tx_pd->pkt_delay_2ms =
		mwifiex_wmm_compute_drv_pkt_delay(priv, skb);
	local_tx_pd->bss_num = priv->bss_num;
	local_tx_pd->bss_type = priv->bss_type;
	/* Always zero as the data is followed by struct txpd */
	local_tx_pd->tx_pkt_offset = cpu_to_le16(sizeof(struct txpd));
	local_tx_pd->tx_pkt_type = cpu_to_le16(PKT_TYPE_AMSDU);
	local_tx_pd->tx_pkt_length = cpu_to_le16(skb->len -
						 sizeof(*local_tx_pd));

	if (tx_info->flags & MWIFIEX_BUF_FLAG_TDLS_PKT)
		local_tx_pd->flags |= MWIFIEX_TXPD_FLAGS_TDLS_PACKET;

	if (local_tx_pd->tx_control == 0)
		/* TxCtrl set by user or default */
		local_tx_pd->tx_control = cpu_to_le32(priv->pkt_tx_ctrl);

	if (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA &&
	    priv->adapter->pps_uapsd_mode) {
		if (true == mwifiex_check_last_packet_indication(priv)) {
			priv->adapter->tx_lock_flag = true;
			local_tx_pd->flags =
				MWIFIEX_TxPD_POWER_MGMT_LAST_PACKET;
		}
	}
}