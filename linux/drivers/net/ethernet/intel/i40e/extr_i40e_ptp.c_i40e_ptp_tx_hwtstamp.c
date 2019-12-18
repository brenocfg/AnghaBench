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
typedef  int u64 ;
typedef  int u32 ;
struct skb_shared_hwtstamps {int dummy; } ;
struct sk_buff {int dummy; } ;
struct i40e_hw {int dummy; } ;
struct i40e_pf {int flags; int /*<<< orphan*/  state; struct sk_buff* ptp_tx_skb; int /*<<< orphan*/  ptp_tx; struct i40e_hw hw; } ;

/* Variables and functions */
 int I40E_FLAG_PTP ; 
 int /*<<< orphan*/  I40E_PRTTSYN_TXTIME_H ; 
 int /*<<< orphan*/  I40E_PRTTSYN_TXTIME_L ; 
 int /*<<< orphan*/  __I40E_PTP_TX_IN_PROGRESS ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  i40e_ptp_convert_to_hwtstamp (struct skb_shared_hwtstamps*,int) ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_tstamp_tx (struct sk_buff*,struct skb_shared_hwtstamps*) ; 

void i40e_ptp_tx_hwtstamp(struct i40e_pf *pf)
{
	struct skb_shared_hwtstamps shhwtstamps;
	struct sk_buff *skb = pf->ptp_tx_skb;
	struct i40e_hw *hw = &pf->hw;
	u32 hi, lo;
	u64 ns;

	if (!(pf->flags & I40E_FLAG_PTP) || !pf->ptp_tx)
		return;

	/* don't attempt to timestamp if we don't have an skb */
	if (!pf->ptp_tx_skb)
		return;

	lo = rd32(hw, I40E_PRTTSYN_TXTIME_L);
	hi = rd32(hw, I40E_PRTTSYN_TXTIME_H);

	ns = (((u64)hi) << 32) | lo;
	i40e_ptp_convert_to_hwtstamp(&shhwtstamps, ns);

	/* Clear the bit lock as soon as possible after reading the register,
	 * and prior to notifying the stack via skb_tstamp_tx(). Otherwise
	 * applications might wake up and attempt to request another transmit
	 * timestamp prior to the bit lock being cleared.
	 */
	pf->ptp_tx_skb = NULL;
	clear_bit_unlock(__I40E_PTP_TX_IN_PROGRESS, pf->state);

	/* Notify the stack and free the skb after we've unlocked */
	skb_tstamp_tx(skb, &shhwtstamps);
	dev_kfree_skb_any(skb);
}