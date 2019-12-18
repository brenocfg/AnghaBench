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
typedef  size_t u8 ;
struct sk_buff {int dummy; } ;
struct rtl_tx_desc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq_th_lock; } ;
struct rtl_priv {TYPE_3__* cfg; TYPE_1__ locks; } ;
struct rtl_pci {struct rtl8192_tx_ring* tx_ring; } ;
struct rtl8192_tx_ring {int /*<<< orphan*/  queue; struct rtl_tx_desc* desc; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* tx_polling ) (struct ieee80211_hw*,size_t) ;int /*<<< orphan*/  (* fill_tx_cmddesc ) (struct ieee80211_hw*,size_t*,int,int,struct sk_buff*) ;int /*<<< orphan*/  (* get_desc ) (struct ieee80211_hw*,size_t*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t BEACON_QUEUE ; 
 int /*<<< orphan*/  HW_DESC_OWN ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,size_t*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*,size_t*,int,int,struct sk_buff*) ; 
 int /*<<< orphan*/  stub3 (struct ieee80211_hw*,size_t) ; 

__attribute__((used)) static bool _rtl92d_cmd_send_packet(struct ieee80211_hw *hw,
				    struct sk_buff *skb)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl8192_tx_ring *ring;
	struct rtl_tx_desc *pdesc;
	u8 idx = 0;
	unsigned long flags;
	struct sk_buff *pskb;

	ring = &rtlpci->tx_ring[BEACON_QUEUE];
	pskb = __skb_dequeue(&ring->queue);
	kfree_skb(pskb);
	spin_lock_irqsave(&rtlpriv->locks.irq_th_lock, flags);
	pdesc = &ring->desc[idx];
	/* discard output from call below */
	rtlpriv->cfg->ops->get_desc(hw, (u8 *)pdesc, true, HW_DESC_OWN);
	rtlpriv->cfg->ops->fill_tx_cmddesc(hw, (u8 *) pdesc, 1, 1, skb);
	__skb_queue_tail(&ring->queue, skb);
	spin_unlock_irqrestore(&rtlpriv->locks.irq_th_lock, flags);
	rtlpriv->cfg->ops->tx_polling(hw, BEACON_QUEUE);
	return true;
}