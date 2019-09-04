#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nvkm_device {int dummy; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ base; } ;
struct gm20b_clk {TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPCPLL_DVFS0 ; 
 int GPCPLL_DVFS0_DFS_COEFF_MASK ; 
 int GPCPLL_DVFS0_DFS_COEFF_SHIFT ; 
 int /*<<< orphan*/  GPC_BCAST_GPCPLL_DVFS2 ; 
 int GPC_BCAST_GPCPLL_DVFS2_DFS_EXT_STROBE_BIT ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
gm20b_dvfs_program_coeff(struct gm20b_clk *clk, u32 coeff)
{
	struct nvkm_device *device = clk->base.base.subdev.device;

	/* strobe to read external DFS coefficient */
	nvkm_mask(device, GPC_BCAST_GPCPLL_DVFS2,
		  GPC_BCAST_GPCPLL_DVFS2_DFS_EXT_STROBE_BIT,
		  GPC_BCAST_GPCPLL_DVFS2_DFS_EXT_STROBE_BIT);

	nvkm_mask(device, GPCPLL_DVFS0, GPCPLL_DVFS0_DFS_COEFF_MASK,
		  coeff << GPCPLL_DVFS0_DFS_COEFF_SHIFT);

	udelay(1);
	nvkm_mask(device, GPC_BCAST_GPCPLL_DVFS2,
		  GPC_BCAST_GPCPLL_DVFS2_DFS_EXT_STROBE_BIT, 0);
}