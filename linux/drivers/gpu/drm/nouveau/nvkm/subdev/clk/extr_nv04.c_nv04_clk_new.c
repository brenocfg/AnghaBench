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
struct nvkm_device {int dummy; } ;
struct nvkm_clk {int /*<<< orphan*/  pll_prog; int /*<<< orphan*/  pll_calc; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv04_clk ; 
 int /*<<< orphan*/  nv04_clk_pll_calc ; 
 int /*<<< orphan*/  nv04_clk_pll_prog ; 
 int nvkm_clk_new_ (int /*<<< orphan*/ *,struct nvkm_device*,int,int,struct nvkm_clk**) ; 

int
nv04_clk_new(struct nvkm_device *device, int index, struct nvkm_clk **pclk)
{
	int ret = nvkm_clk_new_(&nv04_clk, device, index, false, pclk);
	if (ret == 0) {
		(*pclk)->pll_calc = nv04_clk_pll_calc;
		(*pclk)->pll_prog = nv04_clk_pll_prog;
	}
	return ret;
}