#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct sk_buff {int dummy; } ;
struct rtl_tcb_desc {int dummy; } ;
struct TYPE_15__ {int /*<<< orphan*/  waitq_lock; } ;
struct TYPE_14__ {scalar_t__ rfpwr_state; } ;
struct TYPE_11__ {scalar_t__ switch_in_process; } ;
struct TYPE_10__ {scalar_t__ supp_phymode_switch; } ;
struct TYPE_9__ {int /*<<< orphan*/  earlymode_enable; } ;
struct rtl_priv {TYPE_8__* intf_ops; TYPE_7__ locks; TYPE_6__ psc; TYPE_5__* buddy_priv; TYPE_3__ easy_concurrent_ctl; TYPE_2__ dm; TYPE_1__ rtlhal; } ;
struct rtl_pci {struct rtl8192_tx_ring* tx_ring; } ;
struct rtl_mac {int /*<<< orphan*/ * skb_waitq; int /*<<< orphan*/  act_scanning; } ;
struct rtl_hal {scalar_t__ max_earlymode_num; } ;
struct rtl8192_tx_ring {scalar_t__ entries; int /*<<< orphan*/  queue; } ;
struct ieee80211_tx_info {int flags; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* adapter_tx ) (struct ieee80211_hw*,int /*<<< orphan*/ *,struct sk_buff*,struct rtl_tcb_desc*) ;} ;
struct TYPE_12__ {scalar_t__ switch_in_process; } ;
struct TYPE_13__ {TYPE_4__ easy_concurrent_ctl; } ;

/* Variables and functions */
 scalar_t__ ERFON ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 int /*<<< orphan*/  _rtl_update_earlymode_info (struct ieee80211_hw*,struct sk_buff*,struct rtl_tcb_desc*,int) ; 
 size_t* ac_to_hwq ; 
 int /*<<< orphan*/  memset (struct rtl_tcb_desc*,int /*<<< orphan*/ ,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 size_t rtl_tid_to_ac (int) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ *,struct sk_buff*,struct rtl_tcb_desc*) ; 

__attribute__((used)) static void _rtl_pci_tx_chk_waitq(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct sk_buff *skb = NULL;
	struct ieee80211_tx_info *info = NULL;
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	int tid;

	if (!rtlpriv->rtlhal.earlymode_enable)
		return;

	if (rtlpriv->dm.supp_phymode_switch &&
	    (rtlpriv->easy_concurrent_ctl.switch_in_process ||
	    (rtlpriv->buddy_priv &&
	    rtlpriv->buddy_priv->easy_concurrent_ctl.switch_in_process)))
		return;
	/* we just use em for BE/BK/VI/VO */
	for (tid = 7; tid >= 0; tid--) {
		u8 hw_queue = ac_to_hwq[rtl_tid_to_ac(tid)];
		struct rtl8192_tx_ring *ring = &rtlpci->tx_ring[hw_queue];

		while (!mac->act_scanning &&
		       rtlpriv->psc.rfpwr_state == ERFON) {
			struct rtl_tcb_desc tcb_desc;

			memset(&tcb_desc, 0, sizeof(struct rtl_tcb_desc));

			spin_lock(&rtlpriv->locks.waitq_lock);
			if (!skb_queue_empty(&mac->skb_waitq[tid]) &&
			    (ring->entries - skb_queue_len(&ring->queue) >
			     rtlhal->max_earlymode_num)) {
				skb = skb_dequeue(&mac->skb_waitq[tid]);
			} else {
				spin_unlock(&rtlpriv->locks.waitq_lock);
				break;
			}
			spin_unlock(&rtlpriv->locks.waitq_lock);

			/* Some macaddr can't do early mode. like
			 * multicast/broadcast/no_qos data
			 */
			info = IEEE80211_SKB_CB(skb);
			if (info->flags & IEEE80211_TX_CTL_AMPDU)
				_rtl_update_earlymode_info(hw, skb,
							   &tcb_desc, tid);

			rtlpriv->intf_ops->adapter_tx(hw, NULL, skb, &tcb_desc);
		}
	}
}