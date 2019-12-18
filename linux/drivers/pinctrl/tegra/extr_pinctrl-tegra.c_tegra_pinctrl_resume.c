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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_pmx {unsigned int nbanks; int /*<<< orphan*/ ** regs; int /*<<< orphan*/ * backup_regs; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct tegra_pmx* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  readl_relaxed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmb () ; 
 size_t tegra_pinctrl_get_bank_size (struct device*,unsigned int) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_pinctrl_resume(struct device *dev)
{
	struct tegra_pmx *pmx = dev_get_drvdata(dev);
	u32 *backup_regs = pmx->backup_regs;
	u32 *regs;
	size_t bank_size;
	unsigned int i, k;

	for (i = 0; i < pmx->nbanks; i++) {
		bank_size = tegra_pinctrl_get_bank_size(dev, i);
		regs = pmx->regs[i];
		for (k = 0; k < bank_size; k++)
			writel_relaxed(*backup_regs++, regs++);
	}

	/* flush all the prior writes */
	readl_relaxed(pmx->regs[0]);
	/* wait for pinctrl register read to complete */
	rmb();
	return 0;
}