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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_TIMX (int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  cvm_oct_tx_cleanup_tasklet ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t cvm_oct_tx_cleanup_watchdog(int cpl, void *dev_id)
{
	/* Disable the interrupt.  */
	cvmx_write_csr(CVMX_CIU_TIMX(1), 0);
	/* Do the work in the tasklet.  */
	tasklet_schedule(&cvm_oct_tx_cleanup_tasklet);
	return IRQ_HANDLED;
}