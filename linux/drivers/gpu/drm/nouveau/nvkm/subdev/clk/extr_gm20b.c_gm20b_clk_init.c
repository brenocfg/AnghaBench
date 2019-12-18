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
struct nvkm_volt {int dummy; } ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {struct nvkm_volt* volt; } ;
struct nvkm_clk {TYPE_3__* func; } ;
struct gm20b_clk {int /*<<< orphan*/  uv; } ;
struct TYPE_4__ {struct gm20b_clk* (* func ) (struct nvkm_clk*) ;struct nvkm_subdev subdev; } ;
struct gk20a_clk {TYPE_1__ base; } ;
struct TYPE_6__ {int (* prog ) (struct nvkm_clk*) ;TYPE_2__* pstates; int /*<<< orphan*/  (* calc ) (struct nvkm_clk*,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int BYPASSCTRL_SYS ; 
 int BYPASSCTRL_SYS_GPCPLL_SHIFT ; 
 int /*<<< orphan*/  BYPASSCTRL_SYS_GPCPLL_WIDTH ; 
 int GPC2CLK_OUT ; 
 int GPC2CLK_OUT_INIT_MASK ; 
 int GPC2CLK_OUT_INIT_VAL ; 
 int GPCPLL_CFG ; 
 int GPCPLL_CFG_IDDQ ; 
 int MASK (int /*<<< orphan*/ ) ; 
 struct gk20a_clk* gk20a_clk (struct nvkm_clk*) ; 
 int gk20a_clk_setup_slide (struct gk20a_clk*) ; 
 struct gm20b_clk* gm20b_clk (struct nvkm_clk*) ; 
 int gm20b_clk_init_dvfs (struct gm20b_clk*) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_volt_get (struct nvkm_volt*) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_clk*,int /*<<< orphan*/ *) ; 
 int stub2 (struct nvkm_clk*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
gm20b_clk_init(struct nvkm_clk *base)
{
	struct gk20a_clk *clk = gk20a_clk(base);
	struct nvkm_subdev *subdev = &clk->base.subdev;
	struct nvkm_device *device = subdev->device;
	int ret;
	u32 data;

	/* get out from IDDQ */
	nvkm_mask(device, GPCPLL_CFG, GPCPLL_CFG_IDDQ, 0);
	nvkm_rd32(device, GPCPLL_CFG);
	udelay(5);

	nvkm_mask(device, GPC2CLK_OUT, GPC2CLK_OUT_INIT_MASK,
		  GPC2CLK_OUT_INIT_VAL);

	/* Set the global bypass control to VCO */
	nvkm_mask(device, BYPASSCTRL_SYS,
	       MASK(BYPASSCTRL_SYS_GPCPLL_WIDTH) << BYPASSCTRL_SYS_GPCPLL_SHIFT,
	       0);

	ret = gk20a_clk_setup_slide(clk);
	if (ret)
		return ret;

	/* If not fused, set RAM SVOP PDP data 0x2, and enable fuse override */
	data = nvkm_rd32(device, 0x021944);
	if (!(data & 0x3)) {
		data |= 0x2;
		nvkm_wr32(device, 0x021944, data);

		data = nvkm_rd32(device, 0x021948);
		data |=  0x1;
		nvkm_wr32(device, 0x021948, data);
	}

	/* Disable idle slow down  */
	nvkm_mask(device, 0x20160, 0x003f0000, 0x0);

	/* speedo >= 1? */
	if (clk->base.func == &gm20b_clk) {
		struct gm20b_clk *_clk = gm20b_clk(base);
		struct nvkm_volt *volt = device->volt;

		/* Get current voltage */
		_clk->uv = nvkm_volt_get(volt);

		/* Initialize DVFS */
		ret = gm20b_clk_init_dvfs(_clk);
		if (ret)
			return ret;
	}

	/* Start with lowest frequency */
	base->func->calc(base, &base->func->pstates[0].base);
	ret = base->func->prog(base);
	if (ret) {
		nvkm_error(subdev, "cannot initialize clock\n");
		return ret;
	}

	return 0;
}