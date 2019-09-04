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
struct nvkm_subdev {int dummy; } ;
struct nvkm_volt {int max_uv; int vid_nr; TYPE_2__* vid; TYPE_1__* func; struct nvkm_subdev subdev; } ;
struct TYPE_4__ {int uv; int /*<<< orphan*/  vid; } ;
struct TYPE_3__ {int (* volt_set ) (struct nvkm_volt*,int) ;int (* vid_set ) (struct nvkm_volt*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,int,int,int) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int) ; 
 int stub1 (struct nvkm_volt*,int) ; 
 int stub2 (struct nvkm_volt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvkm_volt_set(struct nvkm_volt *volt, u32 uv)
{
	struct nvkm_subdev *subdev = &volt->subdev;
	int i, ret = -EINVAL, best_err = volt->max_uv, best = -1;

	if (volt->func->volt_set)
		return volt->func->volt_set(volt, uv);

	for (i = 0; i < volt->vid_nr; i++) {
		int err = volt->vid[i].uv - uv;
		if (err < 0 || err > best_err)
			continue;

		best_err = err;
		best = i;
		if (best_err == 0)
			break;
	}

	if (best == -1) {
		nvkm_error(subdev, "couldn't set %iuv\n", uv);
		return ret;
	}

	ret = volt->func->vid_set(volt, volt->vid[best].vid);
	nvkm_debug(subdev, "set req %duv to %duv: %d\n", uv,
		   volt->vid[best].uv, ret);
	return ret;
}