#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tx_sa {int mode; int /*<<< orphan*/  salt; int /*<<< orphan*/  key; TYPE_2__* xs; scalar_t__ used; } ;
struct rx_sa {int mode; int /*<<< orphan*/  iptbl_ind; int /*<<< orphan*/  salt; int /*<<< orphan*/  key; TYPE_2__* xs; scalar_t__ used; } ;
struct rx_ip_sa {int /*<<< orphan*/  ipaddr; scalar_t__ used; } ;
struct ixgbe_ipsec {struct rx_ip_sa* ip_tbl; struct tx_sa* tx_tbl; struct rx_sa* rx_tbl; } ;
struct ixgbe_hw {int dummy; } ;
struct ixgbe_adapter {int flags2; struct ixgbe_hw hw; struct ixgbe_ipsec* ipsec; } ;
struct TYPE_3__ {int /*<<< orphan*/  spi; } ;
struct TYPE_4__ {TYPE_1__ id; } ;

/* Variables and functions */
 int IXGBE_FLAG2_IPSEC_ENABLED ; 
 int IXGBE_IPSEC_MAX_RX_IP_COUNT ; 
 int IXGBE_IPSEC_MAX_SA_COUNT ; 
 int IXGBE_RXTXMOD_VF ; 
 int /*<<< orphan*/  ixgbe_ipsec_clear_hw_tables (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_ipsec_del_sa (TYPE_2__*) ; 
 int /*<<< orphan*/  ixgbe_ipsec_set_rx_ip (struct ixgbe_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_ipsec_set_rx_sa (struct ixgbe_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_ipsec_set_tx_sa (struct ixgbe_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_ipsec_start_engine (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_ipsec_stop_engine (struct ixgbe_adapter*) ; 

void ixgbe_ipsec_restore(struct ixgbe_adapter *adapter)
{
	struct ixgbe_ipsec *ipsec = adapter->ipsec;
	struct ixgbe_hw *hw = &adapter->hw;
	int i;

	if (!(adapter->flags2 & IXGBE_FLAG2_IPSEC_ENABLED))
		return;

	/* clean up and restart the engine */
	ixgbe_ipsec_stop_engine(adapter);
	ixgbe_ipsec_clear_hw_tables(adapter);
	ixgbe_ipsec_start_engine(adapter);

	/* reload the Rx and Tx keys */
	for (i = 0; i < IXGBE_IPSEC_MAX_SA_COUNT; i++) {
		struct rx_sa *r = &ipsec->rx_tbl[i];
		struct tx_sa *t = &ipsec->tx_tbl[i];

		if (r->used) {
			if (r->mode & IXGBE_RXTXMOD_VF)
				ixgbe_ipsec_del_sa(r->xs);
			else
				ixgbe_ipsec_set_rx_sa(hw, i, r->xs->id.spi,
						      r->key, r->salt,
						      r->mode, r->iptbl_ind);
		}

		if (t->used) {
			if (t->mode & IXGBE_RXTXMOD_VF)
				ixgbe_ipsec_del_sa(t->xs);
			else
				ixgbe_ipsec_set_tx_sa(hw, i, t->key, t->salt);
		}
	}

	/* reload the IP addrs */
	for (i = 0; i < IXGBE_IPSEC_MAX_RX_IP_COUNT; i++) {
		struct rx_ip_sa *ipsa = &ipsec->ip_tbl[i];

		if (ipsa->used)
			ixgbe_ipsec_set_rx_ip(hw, i, ipsa->ipaddr);
	}
}