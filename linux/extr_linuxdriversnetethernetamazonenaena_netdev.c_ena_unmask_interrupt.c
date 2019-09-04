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
struct ena_ring {int /*<<< orphan*/  ena_com_io_cq; int /*<<< orphan*/  smoothed_interval; } ;
struct ena_eth_io_intr_reg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ena_com_unmask_intr (int /*<<< orphan*/ ,struct ena_eth_io_intr_reg*) ; 
 int /*<<< orphan*/  ena_com_update_intr_reg (struct ena_eth_io_intr_reg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void ena_unmask_interrupt(struct ena_ring *tx_ring,
					struct ena_ring *rx_ring)
{
	struct ena_eth_io_intr_reg intr_reg;

	/* Update intr register: rx intr delay,
	 * tx intr delay and interrupt unmask
	 */
	ena_com_update_intr_reg(&intr_reg,
				rx_ring->smoothed_interval,
				tx_ring->smoothed_interval,
				true);

	/* It is a shared MSI-X.
	 * Tx and Rx CQ have pointer to it.
	 * So we use one of them to reach the intr reg
	 */
	ena_com_unmask_intr(rx_ring->ena_com_io_cq, &intr_reg);
}