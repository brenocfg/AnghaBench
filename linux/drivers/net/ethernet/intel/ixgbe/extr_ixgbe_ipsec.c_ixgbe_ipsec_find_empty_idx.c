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
typedef  size_t u32 ;
struct ixgbe_ipsec {size_t num_rx_sa; size_t num_tx_sa; TYPE_2__* tx_tbl; TYPE_1__* rx_tbl; } ;
struct TYPE_4__ {int /*<<< orphan*/  used; } ;
struct TYPE_3__ {int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int ENOSPC ; 
 size_t IXGBE_IPSEC_MAX_SA_COUNT ; 

__attribute__((used)) static int ixgbe_ipsec_find_empty_idx(struct ixgbe_ipsec *ipsec, bool rxtable)
{
	u32 i;

	if (rxtable) {
		if (ipsec->num_rx_sa == IXGBE_IPSEC_MAX_SA_COUNT)
			return -ENOSPC;

		/* search rx sa table */
		for (i = 0; i < IXGBE_IPSEC_MAX_SA_COUNT; i++) {
			if (!ipsec->rx_tbl[i].used)
				return i;
		}
	} else {
		if (ipsec->num_tx_sa == IXGBE_IPSEC_MAX_SA_COUNT)
			return -ENOSPC;

		/* search tx sa table */
		for (i = 0; i < IXGBE_IPSEC_MAX_SA_COUNT; i++) {
			if (!ipsec->tx_tbl[i].used)
				return i;
		}
	}

	return -ENOSPC;
}