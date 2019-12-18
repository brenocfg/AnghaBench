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
typedef  scalar_t__ u32 ;
struct ixgbe_ipsec {TYPE_2__* tx_tbl; scalar_t__ num_tx_sa; TYPE_1__* rx_tbl; scalar_t__ num_rx_sa; } ;
struct ixgbe_adapter {struct ixgbe_ipsec* ipsec; } ;
struct TYPE_4__ {int mode; scalar_t__ vf; int /*<<< orphan*/  xs; int /*<<< orphan*/  used; } ;
struct TYPE_3__ {int mode; scalar_t__ vf; int /*<<< orphan*/  xs; int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int IXGBE_IPSEC_MAX_SA_COUNT ; 
 int IXGBE_RXTXMOD_VF ; 
 int /*<<< orphan*/  ixgbe_ipsec_del_sa (int /*<<< orphan*/ ) ; 

void ixgbe_ipsec_vf_clear(struct ixgbe_adapter *adapter, u32 vf)
{
	struct ixgbe_ipsec *ipsec = adapter->ipsec;
	int i;

	if (!ipsec)
		return;

	/* search rx sa table */
	for (i = 0; i < IXGBE_IPSEC_MAX_SA_COUNT && ipsec->num_rx_sa; i++) {
		if (!ipsec->rx_tbl[i].used)
			continue;
		if (ipsec->rx_tbl[i].mode & IXGBE_RXTXMOD_VF &&
		    ipsec->rx_tbl[i].vf == vf)
			ixgbe_ipsec_del_sa(ipsec->rx_tbl[i].xs);
	}

	/* search tx sa table */
	for (i = 0; i < IXGBE_IPSEC_MAX_SA_COUNT && ipsec->num_tx_sa; i++) {
		if (!ipsec->tx_tbl[i].used)
			continue;
		if (ipsec->tx_tbl[i].mode & IXGBE_RXTXMOD_VF &&
		    ipsec->tx_tbl[i].vf == vf)
			ixgbe_ipsec_del_sa(ipsec->tx_tbl[i].xs);
	}
}