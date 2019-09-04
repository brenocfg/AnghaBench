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
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct port_info {int /*<<< orphan*/  port_id; } ;
struct adapter {int /*<<< orphan*/  ptp_lock; int /*<<< orphan*/ * ptp_tx_skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PORT_TX_TS_VAL_HI ; 
 int /*<<< orphan*/  MAC_PORT_TX_TS_VAL_LO ; 
 int /*<<< orphan*/  T5_PORT_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ns_to_ktime (int) ; 
 struct skb_shared_hwtstamps* skb_hwtstamps (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_tstamp_tx (int /*<<< orphan*/ *,struct skb_shared_hwtstamps*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

void cxgb4_ptp_read_hwstamp(struct adapter *adapter, struct port_info *pi)
{
	struct skb_shared_hwtstamps *skb_ts = NULL;
	u64 tx_ts;

	skb_ts = skb_hwtstamps(adapter->ptp_tx_skb);

	tx_ts = t4_read_reg(adapter,
			    T5_PORT_REG(pi->port_id, MAC_PORT_TX_TS_VAL_LO));

	tx_ts |= (u64)t4_read_reg(adapter,
				  T5_PORT_REG(pi->port_id,
					      MAC_PORT_TX_TS_VAL_HI)) << 32;
	skb_ts->hwtstamp = ns_to_ktime(tx_ts);
	skb_tstamp_tx(adapter->ptp_tx_skb, skb_ts);
	dev_kfree_skb_any(adapter->ptp_tx_skb);
	spin_lock(&adapter->ptp_lock);
	adapter->ptp_tx_skb = NULL;
	spin_unlock(&adapter->ptp_lock);
}