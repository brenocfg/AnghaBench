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
struct nvkm_clk {int dummy; } ;
struct gk20a_clk {int /*<<< orphan*/  pll; } ;

/* Variables and functions */
 struct gk20a_clk* gk20a_clk (struct nvkm_clk*) ; 
 int gk20a_pllg_program_mnp (struct gk20a_clk*,int /*<<< orphan*/ *) ; 
 int gk20a_pllg_program_mnp_slide (struct gk20a_clk*,int /*<<< orphan*/ *) ; 

int
gk20a_clk_prog(struct nvkm_clk *base)
{
	struct gk20a_clk *clk = gk20a_clk(base);
	int ret;

	ret = gk20a_pllg_program_mnp_slide(clk, &clk->pll);
	if (ret)
		ret = gk20a_pllg_program_mnp(clk, &clk->pll);

	return ret;
}