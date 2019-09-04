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
struct nvkm_pm {int dummy; } ;
struct nvkm_object {int dummy; } ;
struct nvkm_perfdom {TYPE_2__* func; scalar_t__* ctr; TYPE_1__* perfmon; struct nvkm_object object; } ;
struct nvif_perfdom_init {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* next ) (struct nvkm_pm*,struct nvkm_perfdom*) ;int /*<<< orphan*/  (* init ) (struct nvkm_pm*,struct nvkm_perfdom*,scalar_t__) ;} ;
struct TYPE_3__ {struct nvkm_pm* pm; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  nvif_ioctl (struct nvkm_object*,char*,...) ; 
 int nvif_unvers (int,void**,int /*<<< orphan*/ *,struct nvif_perfdom_init) ; 
 int /*<<< orphan*/  nvkm_perfsrc_enable (struct nvkm_pm*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_pm*,struct nvkm_perfdom*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct nvkm_pm*,struct nvkm_perfdom*) ; 

__attribute__((used)) static int
nvkm_perfdom_init(struct nvkm_perfdom *dom, void *data, u32 size)
{
	union {
		struct nvif_perfdom_init none;
	} *args = data;
	struct nvkm_object *object = &dom->object;
	struct nvkm_pm *pm = dom->perfmon->pm;
	int ret = -ENOSYS, i;

	nvif_ioctl(object, "perfdom init size %d\n", size);
	if (!(ret = nvif_unvers(ret, &data, &size, args->none))) {
		nvif_ioctl(object, "perfdom init\n");
	} else
		return ret;

	for (i = 0; i < 4; i++) {
		if (dom->ctr[i]) {
			dom->func->init(pm, dom, dom->ctr[i]);

			/* enable sources */
			nvkm_perfsrc_enable(pm, dom->ctr[i]);
		}
	}

	/* start next batch of counters for sampling */
	dom->func->next(pm, dom);
	return 0;
}