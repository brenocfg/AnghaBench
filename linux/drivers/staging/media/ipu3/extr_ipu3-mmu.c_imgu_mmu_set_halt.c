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
struct imgu_mmu {int /*<<< orphan*/  dev; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ REG_GP_HALT ; 
 scalar_t__ REG_GP_HALTED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*) ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void imgu_mmu_set_halt(struct imgu_mmu *mmu, bool halt)
{
	int ret;
	u32 val;

	writel(halt, mmu->base + REG_GP_HALT);
	ret = readl_poll_timeout(mmu->base + REG_GP_HALTED,
				 val, (val & 1) == halt, 1000, 100000);

	if (ret)
		dev_err(mmu->dev, "failed to %s CIO gate halt\n",
			halt ? "set" : "clear");
}