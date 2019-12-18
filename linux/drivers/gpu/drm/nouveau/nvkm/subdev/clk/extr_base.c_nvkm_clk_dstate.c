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
struct nvkm_clk {int dstate; scalar_t__ state_nr; } ;

/* Variables and functions */
 int max (int,int /*<<< orphan*/ ) ; 
 int min (int,scalar_t__) ; 
 int nvkm_pstate_calc (struct nvkm_clk*,int) ; 

int
nvkm_clk_dstate(struct nvkm_clk *clk, int req, int rel)
{
	if (!rel) clk->dstate  = req;
	if ( rel) clk->dstate += rel;
	clk->dstate = min(clk->dstate, clk->state_nr - 1);
	clk->dstate = max(clk->dstate, 0);
	return nvkm_pstate_calc(clk, true);
}