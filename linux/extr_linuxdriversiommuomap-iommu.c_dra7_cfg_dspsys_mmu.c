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
struct omap_iommu {int id; int /*<<< orphan*/  syscfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSP_SYS_MMU_CONFIG ; 
 int DSP_SYS_MMU_CONFIG_EN_SHIFT ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void dra7_cfg_dspsys_mmu(struct omap_iommu *obj, bool enable)
{
	u32 val, mask;

	if (!obj->syscfg)
		return;

	mask = (1 << (obj->id * DSP_SYS_MMU_CONFIG_EN_SHIFT));
	val = enable ? mask : 0;
	regmap_update_bits(obj->syscfg, DSP_SYS_MMU_CONFIG, mask, val);
}