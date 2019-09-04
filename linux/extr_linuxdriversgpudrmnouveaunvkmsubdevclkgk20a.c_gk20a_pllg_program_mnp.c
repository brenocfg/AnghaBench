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
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {int dummy; } ;
struct gk20a_pll {int dummy; } ;
struct TYPE_2__ {struct nvkm_subdev subdev; } ;
struct gk20a_clk {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPC2CLK_OUT ; 
 int GPC2CLK_OUT_VCODIV1 ; 
 int GPC2CLK_OUT_VCODIV2 ; 
 int /*<<< orphan*/  GPC2CLK_OUT_VCODIV_MASK ; 
 int GPC2CLK_OUT_VCODIV_SHIFT ; 
 int /*<<< orphan*/  gk20a_pllg_disable (struct gk20a_clk*) ; 
 int gk20a_pllg_enable (struct gk20a_clk*) ; 
 int /*<<< orphan*/  gk20a_pllg_read_mnp (struct gk20a_clk*,struct gk20a_pll*) ; 
 int /*<<< orphan*/  gk20a_pllg_write_mnp (struct gk20a_clk*,struct gk20a_pll const*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_rd32 (struct nvkm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
gk20a_pllg_program_mnp(struct gk20a_clk *clk, const struct gk20a_pll *pll)
{
	struct nvkm_subdev *subdev = &clk->base.subdev;
	struct nvkm_device *device = subdev->device;
	struct gk20a_pll cur_pll;
	int ret;

	gk20a_pllg_read_mnp(clk, &cur_pll);

	/* split VCO-to-bypass jump in half by setting out divider 1:2 */
	nvkm_mask(device, GPC2CLK_OUT, GPC2CLK_OUT_VCODIV_MASK,
		  GPC2CLK_OUT_VCODIV2 << GPC2CLK_OUT_VCODIV_SHIFT);
	/* Intentional 2nd write to assure linear divider operation */
	nvkm_mask(device, GPC2CLK_OUT, GPC2CLK_OUT_VCODIV_MASK,
		  GPC2CLK_OUT_VCODIV2 << GPC2CLK_OUT_VCODIV_SHIFT);
	nvkm_rd32(device, GPC2CLK_OUT);
	udelay(2);

	gk20a_pllg_disable(clk);

	gk20a_pllg_write_mnp(clk, pll);

	ret = gk20a_pllg_enable(clk);
	if (ret)
		return ret;

	/* restore out divider 1:1 */
	udelay(2);
	nvkm_mask(device, GPC2CLK_OUT, GPC2CLK_OUT_VCODIV_MASK,
		  GPC2CLK_OUT_VCODIV1 << GPC2CLK_OUT_VCODIV_SHIFT);
	/* Intentional 2nd write to assure linear divider operation */
	nvkm_mask(device, GPC2CLK_OUT, GPC2CLK_OUT_VCODIV_MASK,
		  GPC2CLK_OUT_VCODIV1 << GPC2CLK_OUT_VCODIV_SHIFT);
	nvkm_rd32(device, GPC2CLK_OUT);

	return 0;
}