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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_cstate {int /*<<< orphan*/ * domain; } ;
struct gt215_clk {int /*<<< orphan*/ * eng; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int gt215_pll_info (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
calc_clk(struct gt215_clk *clk, struct nvkm_cstate *cstate,
	 int idx, u32 pll, int dom)
{
	int ret = gt215_pll_info(&clk->base, idx, pll, cstate->domain[dom],
				 &clk->eng[dom]);
	if (ret >= 0)
		return 0;
	return ret;
}