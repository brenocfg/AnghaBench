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
struct wcn36xx_vif {scalar_t__ pw_state; } ;
struct wcn36xx_tx_bd {int dummy; } ;
struct wcn36xx_dxe_desc {int fr_len; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  dst_addr_l; int /*<<< orphan*/  src_addr_l; } ;
struct wcn36xx_dxe_ctl {struct wcn36xx_dxe_ctl* next; struct sk_buff* skb; scalar_t__ bd_cpu_addr; int /*<<< orphan*/  bd_phy_addr; struct wcn36xx_dxe_desc* desc; } ;
struct wcn36xx_dxe_ch {int /*<<< orphan*/  lock; int /*<<< orphan*/  def_ctrl; int /*<<< orphan*/  reg_ctrl; int /*<<< orphan*/  ctrl_bd; int /*<<< orphan*/  ctrl_skb; struct wcn36xx_dxe_ctl* head_blk_ctl; int /*<<< orphan*/  dxe_wq; } ;
struct wcn36xx {int queues_stopped; int /*<<< orphan*/  tx_rings_empty_state; int /*<<< orphan*/  dev; int /*<<< orphan*/  hw; struct wcn36xx_dxe_ch dxe_tx_h_ch; struct wcn36xx_dxe_ch dxe_tx_l_ch; } ;
struct sk_buff {int len; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ WCN36XX_BMPS ; 
 int /*<<< orphan*/  WCN36XX_DBG_DXE ; 
 int /*<<< orphan*/  WCN36XX_DBG_DXE_DUMP ; 
 int /*<<< orphan*/  WCN36XX_SMSM_WLAN_TX_ENABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_stop_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,struct wcn36xx_tx_bd*,int) ; 
 int /*<<< orphan*/  qcom_smem_state_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (scalar_t__) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wcn36xx_dbg_dump (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  wcn36xx_dxe_write_register (struct wcn36xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_err (char*) ; 
 int /*<<< orphan*/  wmb () ; 

int wcn36xx_dxe_tx_frame(struct wcn36xx *wcn,
			 struct wcn36xx_vif *vif_priv,
			 struct wcn36xx_tx_bd *bd,
			 struct sk_buff *skb,
			 bool is_low)
{
	struct wcn36xx_dxe_desc *desc_bd, *desc_skb;
	struct wcn36xx_dxe_ctl *ctl_bd, *ctl_skb;
	struct wcn36xx_dxe_ch *ch = NULL;
	unsigned long flags;
	int ret;

	ch = is_low ? &wcn->dxe_tx_l_ch : &wcn->dxe_tx_h_ch;

	spin_lock_irqsave(&ch->lock, flags);
	ctl_bd = ch->head_blk_ctl;
	ctl_skb = ctl_bd->next;

	/*
	 * If skb is not null that means that we reached the tail of the ring
	 * hence ring is full. Stop queues to let mac80211 back off until ring
	 * has an empty slot again.
	 */
	if (NULL != ctl_skb->skb) {
		ieee80211_stop_queues(wcn->hw);
		wcn->queues_stopped = true;
		spin_unlock_irqrestore(&ch->lock, flags);
		return -EBUSY;
	}

	if (unlikely(ctl_skb->bd_cpu_addr)) {
		wcn36xx_err("bd_cpu_addr cannot be NULL for skb DXE\n");
		ret = -EINVAL;
		goto unlock;
	}

	desc_bd = ctl_bd->desc;
	desc_skb = ctl_skb->desc;

	ctl_bd->skb = NULL;

	/* write buffer descriptor */
	memcpy(ctl_bd->bd_cpu_addr, bd, sizeof(*bd));

	/* Set source address of the BD we send */
	desc_bd->src_addr_l = ctl_bd->bd_phy_addr;
	desc_bd->dst_addr_l = ch->dxe_wq;
	desc_bd->fr_len = sizeof(struct wcn36xx_tx_bd);

	wcn36xx_dbg(WCN36XX_DBG_DXE, "DXE TX\n");

	wcn36xx_dbg_dump(WCN36XX_DBG_DXE_DUMP, "DESC1 >>> ",
			 (char *)desc_bd, sizeof(*desc_bd));
	wcn36xx_dbg_dump(WCN36XX_DBG_DXE_DUMP,
			 "BD   >>> ", (char *)ctl_bd->bd_cpu_addr,
			 sizeof(struct wcn36xx_tx_bd));

	desc_skb->src_addr_l = dma_map_single(wcn->dev,
					      skb->data,
					      skb->len,
					      DMA_TO_DEVICE);
	if (dma_mapping_error(wcn->dev, desc_skb->src_addr_l)) {
		dev_err(wcn->dev, "unable to DMA map src_addr_l\n");
		ret = -ENOMEM;
		goto unlock;
	}

	ctl_skb->skb = skb;
	desc_skb->dst_addr_l = ch->dxe_wq;
	desc_skb->fr_len = ctl_skb->skb->len;

	wcn36xx_dbg_dump(WCN36XX_DBG_DXE_DUMP, "DESC2 >>> ",
			 (char *)desc_skb, sizeof(*desc_skb));
	wcn36xx_dbg_dump(WCN36XX_DBG_DXE_DUMP, "SKB   >>> ",
			 (char *)ctl_skb->skb->data, ctl_skb->skb->len);

	/* Move the head of the ring to the next empty descriptor */
	 ch->head_blk_ctl = ctl_skb->next;

	/* Commit all previous writes and set descriptors to VALID */
	wmb();
	desc_skb->ctrl = ch->ctrl_skb;
	wmb();
	desc_bd->ctrl = ch->ctrl_bd;

	/*
	 * When connected and trying to send data frame chip can be in sleep
	 * mode and writing to the register will not wake up the chip. Instead
	 * notify chip about new frame through SMSM bus.
	 */
	if (is_low &&  vif_priv->pw_state == WCN36XX_BMPS) {
		qcom_smem_state_update_bits(wcn->tx_rings_empty_state,
					    WCN36XX_SMSM_WLAN_TX_ENABLE,
					    WCN36XX_SMSM_WLAN_TX_ENABLE);
	} else {
		/* indicate End Of Packet and generate interrupt on descriptor
		 * done.
		 */
		wcn36xx_dxe_write_register(wcn,
			ch->reg_ctrl, ch->def_ctrl);
	}

	ret = 0;
unlock:
	spin_unlock_irqrestore(&ch->lock, flags);
	return ret;
}