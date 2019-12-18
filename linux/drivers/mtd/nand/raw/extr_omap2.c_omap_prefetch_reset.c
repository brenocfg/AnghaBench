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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  gpmc_prefetch_config1; int /*<<< orphan*/  gpmc_prefetch_control; } ;
struct omap_nand_info {TYPE_1__ reg; } ;

/* Variables and functions */
 int CS_MASK ; 
 int EINVAL ; 
 int PREFETCH_CONFIG1_CS_SHIFT ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_prefetch_reset(int cs, struct omap_nand_info *info)
{
	u32 config1;

	/* check if the same module/cs is trying to reset */
	config1 = readl(info->reg.gpmc_prefetch_config1);
	if (((config1 >> PREFETCH_CONFIG1_CS_SHIFT) & CS_MASK) != cs)
		return -EINVAL;

	/* Stop the PFPW engine */
	writel(0x0, info->reg.gpmc_prefetch_control);

	/* Reset/disable the PFPW engine */
	writel(0x0, info->reg.gpmc_prefetch_config1);

	return 0;
}