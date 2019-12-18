#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nvkm_volt {int vid_nr; TYPE_5__* vid; } ;
struct nvkm_subdev {TYPE_1__* device; } ;
struct TYPE_12__ {int voltage; int /*<<< orphan*/ * domain; } ;
struct nvkm_pstate {TYPE_6__ base; } ;
struct TYPE_9__ {TYPE_2__* func; struct nvkm_subdev subdev; } ;
struct TYPE_10__ {TYPE_3__ base; } ;
struct gm20b_clk {int safe_fmax_vmin; TYPE_4__ base; } ;
struct TYPE_11__ {int uv; int vid; } ;
struct TYPE_8__ {int nr_pstates; struct nvkm_pstate* pstates; } ;
struct TYPE_7__ {struct nvkm_volt* volt; } ;

/* Variables and functions */
 int EINVAL ; 
 int max (int,int /*<<< orphan*/ ) ; 
 size_t nv_clk_src_gpc ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,int) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*) ; 

__attribute__((used)) static int
gm20b_clk_init_safe_fmax(struct gm20b_clk *clk)
{
	struct nvkm_subdev *subdev = &clk->base.base.subdev;
	struct nvkm_volt *volt = subdev->device->volt;
	struct nvkm_pstate *pstates = clk->base.base.func->pstates;
	int nr_pstates = clk->base.base.func->nr_pstates;
	int vmin, id = 0;
	u32 fmax = 0;
	int i;

	/* find lowest voltage we can use */
	vmin = volt->vid[0].uv;
	for (i = 1; i < volt->vid_nr; i++) {
		if (volt->vid[i].uv <= vmin) {
			vmin = volt->vid[i].uv;
			id = volt->vid[i].vid;
		}
	}

	/* find max frequency at this voltage */
	for (i = 0; i < nr_pstates; i++)
		if (pstates[i].base.voltage == id)
			fmax = max(fmax,
				   pstates[i].base.domain[nv_clk_src_gpc]);

	if (!fmax) {
		nvkm_error(subdev, "failed to evaluate safe fmax\n");
		return -EINVAL;
	}

	/* we are safe at 90% of the max frequency */
	clk->safe_fmax_vmin = fmax * (100 - 10) / 100;
	nvkm_debug(subdev, "safe fmax @ vmin = %u Khz\n", clk->safe_fmax_vmin);

	return 0;
}