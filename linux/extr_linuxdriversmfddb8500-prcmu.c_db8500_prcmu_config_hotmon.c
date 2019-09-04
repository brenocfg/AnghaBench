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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int HOTMON_CONFIG_HIGH ; 
 int HOTMON_CONFIG_LOW ; 
 int MB4H_HOTMON ; 
 int MBOX_BIT (int) ; 
 int /*<<< orphan*/  PRCM_MBOX_CPU_SET ; 
 int /*<<< orphan*/  PRCM_MBOX_CPU_VAL ; 
 scalar_t__ PRCM_MBOX_HEADER_REQ_MB4 ; 
 scalar_t__ PRCM_REQ_MB4_HOTMON_CONFIG ; 
 scalar_t__ PRCM_REQ_MB4_HOTMON_HIGH ; 
 scalar_t__ PRCM_REQ_MB4_HOTMON_LOW ; 
 int /*<<< orphan*/  cpu_relax () ; 
 TYPE_1__ mb4_transfer ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int readl (int /*<<< orphan*/ ) ; 
 scalar_t__ tcdm_base ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

int db8500_prcmu_config_hotmon(u8 low, u8 high)
{
	mutex_lock(&mb4_transfer.lock);

	while (readl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(4))
		cpu_relax();

	writeb(low, (tcdm_base + PRCM_REQ_MB4_HOTMON_LOW));
	writeb(high, (tcdm_base + PRCM_REQ_MB4_HOTMON_HIGH));
	writeb((HOTMON_CONFIG_LOW | HOTMON_CONFIG_HIGH),
		(tcdm_base + PRCM_REQ_MB4_HOTMON_CONFIG));
	writeb(MB4H_HOTMON, (tcdm_base + PRCM_MBOX_HEADER_REQ_MB4));

	writel(MBOX_BIT(4), PRCM_MBOX_CPU_SET);
	wait_for_completion(&mb4_transfer.work);

	mutex_unlock(&mb4_transfer.lock);

	return 0;
}