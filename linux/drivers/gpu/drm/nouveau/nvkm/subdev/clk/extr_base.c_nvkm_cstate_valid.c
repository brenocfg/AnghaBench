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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_volt {int /*<<< orphan*/  max_uv; } ;
struct nvkm_domain {size_t name; int flags; } ;
struct nvkm_cstate {int /*<<< orphan*/  voltage; int /*<<< orphan*/ * domain; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct nvkm_clk {int boost_mode; int /*<<< orphan*/  boost_khz; int /*<<< orphan*/  base_khz; TYPE_2__ subdev; struct nvkm_domain* domains; } ;
struct TYPE_3__ {struct nvkm_volt* volt; } ;

/* Variables and functions */
#define  NVKM_CLK_BOOST_BIOS 129 
#define  NVKM_CLK_BOOST_NONE 128 
 int NVKM_CLK_DOM_FLAG_VPSTATE ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t nv_clk_src_max ; 
 int nvkm_volt_map (struct nvkm_volt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
nvkm_cstate_valid(struct nvkm_clk *clk, struct nvkm_cstate *cstate,
		  u32 max_volt, int temp)
{
	const struct nvkm_domain *domain = clk->domains;
	struct nvkm_volt *volt = clk->subdev.device->volt;
	int voltage;

	while (domain && domain->name != nv_clk_src_max) {
		if (domain->flags & NVKM_CLK_DOM_FLAG_VPSTATE) {
			u32 freq = cstate->domain[domain->name];
			switch (clk->boost_mode) {
			case NVKM_CLK_BOOST_NONE:
				if (clk->base_khz && freq > clk->base_khz)
					return false;
				/* fall through */
			case NVKM_CLK_BOOST_BIOS:
				if (clk->boost_khz && freq > clk->boost_khz)
					return false;
			}
		}
		domain++;
	}

	if (!volt)
		return true;

	voltage = nvkm_volt_map(volt, cstate->voltage, temp);
	if (voltage < 0)
		return false;
	return voltage <= min(max_volt, volt->max_uv);
}