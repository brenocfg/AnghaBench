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
struct nvkm_cstate {int* domain; } ;
struct nvkm_clk {int dummy; } ;
struct gk20a_clk {int /*<<< orphan*/  pll; } ;

/* Variables and functions */
 int GK20A_CLK_GPC_MDIV ; 
 struct gk20a_clk* gk20a_clk (struct nvkm_clk*) ; 
 int gk20a_pllg_calc_mnp (struct gk20a_clk*,int,int /*<<< orphan*/ *) ; 
 size_t nv_clk_src_gpc ; 

int
gk20a_clk_calc(struct nvkm_clk *base, struct nvkm_cstate *cstate)
{
	struct gk20a_clk *clk = gk20a_clk(base);

	return gk20a_pllg_calc_mnp(clk, cstate->domain[nv_clk_src_gpc] *
					 GK20A_CLK_GPC_MDIV, &clk->pll);
}