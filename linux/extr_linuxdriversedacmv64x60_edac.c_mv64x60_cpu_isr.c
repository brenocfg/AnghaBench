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
typedef  int u32 ;
struct mv64x60_cpu_pdata {scalar_t__* cpu_vbase; } ;
struct edac_device_ctl_info {struct mv64x60_cpu_pdata* pvt_info; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int MV64x60_CPU_CAUSE_MASK ; 
 scalar_t__ MV64x60_CPU_ERR_CAUSE ; 
 int /*<<< orphan*/  mv64x60_cpu_check (struct edac_device_ctl_info*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static irqreturn_t mv64x60_cpu_isr(int irq, void *dev_id)
{
	struct edac_device_ctl_info *edac_dev = dev_id;
	struct mv64x60_cpu_pdata *pdata = edac_dev->pvt_info;
	u32 cause;

	cause = readl(pdata->cpu_vbase[1] + MV64x60_CPU_ERR_CAUSE) &
	    MV64x60_CPU_CAUSE_MASK;
	if (!cause)
		return IRQ_NONE;

	mv64x60_cpu_check(edac_dev);

	return IRQ_HANDLED;
}