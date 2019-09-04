#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nvkm_device {int dummy; } ;
struct gk20a_pll {int m; int n; int pl; } ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;
struct gk20a_clk {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPCPLL_COEFF ; 
 int GPCPLL_COEFF_M_SHIFT ; 
 int /*<<< orphan*/  GPCPLL_COEFF_M_WIDTH ; 
 int GPCPLL_COEFF_N_SHIFT ; 
 int /*<<< orphan*/  GPCPLL_COEFF_N_WIDTH ; 
 int GPCPLL_COEFF_P_SHIFT ; 
 int /*<<< orphan*/  GPCPLL_COEFF_P_WIDTH ; 
 int MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int /*<<< orphan*/ ,int) ; 

void
gk20a_pllg_write_mnp(struct gk20a_clk *clk, const struct gk20a_pll *pll)
{
	struct nvkm_device *device = clk->base.subdev.device;
	u32 val;

	val = (pll->m & MASK(GPCPLL_COEFF_M_WIDTH)) << GPCPLL_COEFF_M_SHIFT;
	val |= (pll->n & MASK(GPCPLL_COEFF_N_WIDTH)) << GPCPLL_COEFF_N_SHIFT;
	val |= (pll->pl & MASK(GPCPLL_COEFF_P_WIDTH)) << GPCPLL_COEFF_P_SHIFT;
	nvkm_wr32(device, GPCPLL_COEFF, val);
}