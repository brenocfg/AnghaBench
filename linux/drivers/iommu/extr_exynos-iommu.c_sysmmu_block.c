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
struct sysmmu_drvdata {scalar_t__ sfrbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_BLOCK ; 
 scalar_t__ REG_MMU_CTRL ; 
 scalar_t__ REG_MMU_STATUS ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  sysmmu_unblock (struct sysmmu_drvdata*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool sysmmu_block(struct sysmmu_drvdata *data)
{
	int i = 120;

	writel(CTRL_BLOCK, data->sfrbase + REG_MMU_CTRL);
	while ((i > 0) && !(readl(data->sfrbase + REG_MMU_STATUS) & 1))
		--i;

	if (!(readl(data->sfrbase + REG_MMU_STATUS) & 1)) {
		sysmmu_unblock(data);
		return false;
	}

	return true;
}