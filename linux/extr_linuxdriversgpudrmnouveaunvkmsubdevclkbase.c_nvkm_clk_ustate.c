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
struct nvkm_clk {int ustate_ac; int ustate_dc; } ;

/* Variables and functions */
 int nvkm_clk_ustate_update (struct nvkm_clk*,int) ; 
 int nvkm_pstate_calc (struct nvkm_clk*,int) ; 

int
nvkm_clk_ustate(struct nvkm_clk *clk, int req, int pwr)
{
	int ret = nvkm_clk_ustate_update(clk, req);
	if (ret >= 0) {
		if (ret -= 2, pwr) clk->ustate_ac = ret;
		else		   clk->ustate_dc = ret;
		return nvkm_pstate_calc(clk, true);
	}
	return ret;
}