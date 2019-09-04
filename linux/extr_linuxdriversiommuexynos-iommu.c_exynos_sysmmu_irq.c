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
typedef  int sysmmu_iova_t ;
struct sysmmu_fault_info {unsigned int bit; int /*<<< orphan*/  type; scalar_t__ addr_reg; } ;
struct sysmmu_drvdata {int /*<<< orphan*/  lock; int /*<<< orphan*/  clk_master; scalar_t__ sfrbase; int /*<<< orphan*/  master; TYPE_1__* domain; int /*<<< orphan*/  version; int /*<<< orphan*/  active; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct sysmmu_fault_info*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOSYS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MMU_MAJ_VER (int /*<<< orphan*/ ) ; 
 unsigned short REG_INT_CLEAR ; 
 unsigned short REG_INT_STATUS ; 
 unsigned short REG_V5_INT_CLEAR ; 
 unsigned short REG_V5_INT_STATUS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned int __ffs (int) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int report_iommu_fault (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_fault_information (struct sysmmu_drvdata*,struct sysmmu_fault_info const*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct sysmmu_fault_info* sysmmu_faults ; 
 int /*<<< orphan*/  sysmmu_unblock (struct sysmmu_drvdata*) ; 
 struct sysmmu_fault_info* sysmmu_v5_faults ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t exynos_sysmmu_irq(int irq, void *dev_id)
{
	/* SYSMMU is in blocked state when interrupt occurred. */
	struct sysmmu_drvdata *data = dev_id;
	const struct sysmmu_fault_info *finfo;
	unsigned int i, n, itype;
	sysmmu_iova_t fault_addr = -1;
	unsigned short reg_status, reg_clear;
	int ret = -ENOSYS;

	WARN_ON(!data->active);

	if (MMU_MAJ_VER(data->version) < 5) {
		reg_status = REG_INT_STATUS;
		reg_clear = REG_INT_CLEAR;
		finfo = sysmmu_faults;
		n = ARRAY_SIZE(sysmmu_faults);
	} else {
		reg_status = REG_V5_INT_STATUS;
		reg_clear = REG_V5_INT_CLEAR;
		finfo = sysmmu_v5_faults;
		n = ARRAY_SIZE(sysmmu_v5_faults);
	}

	spin_lock(&data->lock);

	clk_enable(data->clk_master);

	itype = __ffs(readl(data->sfrbase + reg_status));
	for (i = 0; i < n; i++, finfo++)
		if (finfo->bit == itype)
			break;
	/* unknown/unsupported fault */
	BUG_ON(i == n);

	/* print debug message */
	fault_addr = readl(data->sfrbase + finfo->addr_reg);
	show_fault_information(data, finfo, fault_addr);

	if (data->domain)
		ret = report_iommu_fault(&data->domain->domain,
					data->master, fault_addr, finfo->type);
	/* fault is not recovered by fault handler */
	BUG_ON(ret != 0);

	writel(1 << itype, data->sfrbase + reg_clear);

	sysmmu_unblock(data);

	clk_disable(data->clk_master);

	spin_unlock(&data->lock);

	return IRQ_HANDLED;
}