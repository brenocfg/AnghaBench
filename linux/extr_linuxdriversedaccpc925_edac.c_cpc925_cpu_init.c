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
struct cpc925_dev_info {scalar_t__ vbase; } ;

/* Variables and functions */
 int CPU_MASK_ENABLE ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 scalar_t__ REG_APIMASK_OFFSET ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 int cpc925_cpu_mask_disabled () ; 
 int /*<<< orphan*/  cpc925_printk (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void cpc925_cpu_init(struct cpc925_dev_info *dev_info)
{
	u32 apimask;
	u32 cpumask;

	apimask = __raw_readl(dev_info->vbase + REG_APIMASK_OFFSET);

	cpumask = cpc925_cpu_mask_disabled();
	if (apimask & cpumask) {
		cpc925_printk(KERN_WARNING, "CPU(s) not present, "
				"but enabled in APIMASK, disabling\n");
		apimask &= ~cpumask;
	}

	if ((apimask & CPU_MASK_ENABLE) == 0)
		apimask |= CPU_MASK_ENABLE;

	__raw_writel(apimask, dev_info->vbase + REG_APIMASK_OFFSET);
}