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
typedef  int /*<<< orphan*/  u16 ;
struct atl1e_tx_ring {int /*<<< orphan*/  next_to_use; } ;
struct atl1e_tpd_desc {int dummy; } ;
struct atl1e_adapter {int /*<<< orphan*/  hw; struct atl1e_tx_ring tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_WRITE_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_MB_TPD_PROD_IDX ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void atl1e_tx_queue(struct atl1e_adapter *adapter, u16 count,
			   struct atl1e_tpd_desc *tpd)
{
	struct atl1e_tx_ring *tx_ring = &adapter->tx_ring;
	/* Force memory writes to complete before letting h/w
	 * know there are new descriptors to fetch.  (Only
	 * applicable for weak-ordered memory model archs,
	 * such as IA-64). */
	wmb();
	AT_WRITE_REG(&adapter->hw, REG_MB_TPD_PROD_IDX, tx_ring->next_to_use);
}