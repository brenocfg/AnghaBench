#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  MB1H_RESET_MODEM ; 
 int MBOX_BIT (int) ; 
 int /*<<< orphan*/  PRCM_MBOX_CPU_SET ; 
 int /*<<< orphan*/  PRCM_MBOX_CPU_VAL ; 
 scalar_t__ PRCM_MBOX_HEADER_REQ_MB1 ; 
 int /*<<< orphan*/  cpu_relax () ; 
 TYPE_1__ mb1_transfer ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int readl (int /*<<< orphan*/ ) ; 
 scalar_t__ tcdm_base ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

void db8500_prcmu_modem_reset(void)
{
	mutex_lock(&mb1_transfer.lock);

	while (readl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(1))
		cpu_relax();

	writeb(MB1H_RESET_MODEM, (tcdm_base + PRCM_MBOX_HEADER_REQ_MB1));
	writel(MBOX_BIT(1), PRCM_MBOX_CPU_SET);
	wait_for_completion(&mb1_transfer.work);

	/*
	 * No need to check return from PRCMU as modem should go in reset state
	 * This state is already managed by upper layer
	 */

	mutex_unlock(&mb1_transfer.lock);
}