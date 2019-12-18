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
struct nvkm_subdev {int dummy; } ;
struct nvkm_device {int /*<<< orphan*/  cfgopt; int /*<<< orphan*/  event; struct nvkm_bios* bios; } ;
struct nvkm_clk_func {int nr_pstates; TYPE_1__* pstates; int /*<<< orphan*/  domains; } ;
struct nvkm_clk {int boost_khz; int base_khz; int ustate_ac; int ustate_dc; int allow_reclock; int state_nr; int /*<<< orphan*/  boost_mode; int /*<<< orphan*/  pwrsrc_ntfy; int /*<<< orphan*/  states; int /*<<< orphan*/  waiting; int /*<<< orphan*/  wait; int /*<<< orphan*/  work; int /*<<< orphan*/  domains; struct nvkm_clk_func const* func; struct nvkm_subdev subdev; } ;
struct nvkm_bios {int dummy; } ;
struct nvbios_vpstate_header {int /*<<< orphan*/  base_id; int /*<<< orphan*/  boost_id; } ;
struct nvbios_vpstate_entry {int clock_mhz; } ;
struct TYPE_2__ {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVKM_CLK_BOOST_NONE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvbios_vpstate_entry (struct nvkm_bios*,struct nvbios_vpstate_header*,int /*<<< orphan*/ ,struct nvbios_vpstate_entry*) ; 
 int /*<<< orphan*/  nvbios_vpstate_parse (struct nvkm_bios*,struct nvbios_vpstate_header*) ; 
 int /*<<< orphan*/  nvkm_clk ; 
 void* nvkm_clk_nstate (struct nvkm_clk*,char const*,int) ; 
 int /*<<< orphan*/  nvkm_clk_pwrsrc ; 
 int /*<<< orphan*/  nvkm_longopt (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int nvkm_notify_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nvkm_pstate_new (struct nvkm_clk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_pstate_work ; 
 char* nvkm_stropt (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  nvkm_subdev_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,struct nvkm_subdev*) ; 

int
nvkm_clk_ctor(const struct nvkm_clk_func *func, struct nvkm_device *device,
	      int index, bool allow_reclock, struct nvkm_clk *clk)
{
	struct nvkm_subdev *subdev = &clk->subdev;
	struct nvkm_bios *bios = device->bios;
	int ret, idx, arglen;
	const char *mode;
	struct nvbios_vpstate_header h;

	nvkm_subdev_ctor(&nvkm_clk, device, index, subdev);

	if (bios && !nvbios_vpstate_parse(bios, &h)) {
		struct nvbios_vpstate_entry base, boost;
		if (!nvbios_vpstate_entry(bios, &h, h.boost_id, &boost))
			clk->boost_khz = boost.clock_mhz * 1000;
		if (!nvbios_vpstate_entry(bios, &h, h.base_id, &base))
			clk->base_khz = base.clock_mhz * 1000;
	}

	clk->func = func;
	INIT_LIST_HEAD(&clk->states);
	clk->domains = func->domains;
	clk->ustate_ac = -1;
	clk->ustate_dc = -1;
	clk->allow_reclock = allow_reclock;

	INIT_WORK(&clk->work, nvkm_pstate_work);
	init_waitqueue_head(&clk->wait);
	atomic_set(&clk->waiting, 0);

	/* If no pstates are provided, try and fetch them from the BIOS */
	if (!func->pstates) {
		idx = 0;
		do {
			ret = nvkm_pstate_new(clk, idx++);
		} while (ret == 0);
	} else {
		for (idx = 0; idx < func->nr_pstates; idx++)
			list_add_tail(&func->pstates[idx].head, &clk->states);
		clk->state_nr = func->nr_pstates;
	}

	ret = nvkm_notify_init(NULL, &device->event, nvkm_clk_pwrsrc, true,
			       NULL, 0, 0, &clk->pwrsrc_ntfy);
	if (ret)
		return ret;

	mode = nvkm_stropt(device->cfgopt, "NvClkMode", &arglen);
	if (mode) {
		clk->ustate_ac = nvkm_clk_nstate(clk, mode, arglen);
		clk->ustate_dc = nvkm_clk_nstate(clk, mode, arglen);
	}

	mode = nvkm_stropt(device->cfgopt, "NvClkModeAC", &arglen);
	if (mode)
		clk->ustate_ac = nvkm_clk_nstate(clk, mode, arglen);

	mode = nvkm_stropt(device->cfgopt, "NvClkModeDC", &arglen);
	if (mode)
		clk->ustate_dc = nvkm_clk_nstate(clk, mode, arglen);

	clk->boost_mode = nvkm_longopt(device->cfgopt, "NvBoost",
				       NVKM_CLK_BOOST_NONE);
	return 0;
}