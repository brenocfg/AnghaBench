#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_pm {int dummy; } ;
struct nvkm_object {int dummy; } ;
struct nvkm_perfdom {scalar_t__ clk; TYPE_3__** ctr; TYPE_2__* func; TYPE_1__* perfmon; struct nvkm_object object; } ;
struct nvif_perfdom_read_v0 {scalar_t__ clk; int /*<<< orphan*/ * ctr; int /*<<< orphan*/  version; } ;
struct TYPE_6__ {int /*<<< orphan*/  ctr; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* read ) (struct nvkm_pm*,struct nvkm_perfdom*,TYPE_3__*) ;} ;
struct TYPE_4__ {struct nvkm_pm* pm; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOSYS ; 
 int /*<<< orphan*/  nvif_ioctl (struct nvkm_object*,char*,int /*<<< orphan*/ ) ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct nvif_perfdom_read_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_pm*,struct nvkm_perfdom*,TYPE_3__*) ; 

__attribute__((used)) static int
nvkm_perfdom_read(struct nvkm_perfdom *dom, void *data, u32 size)
{
	union {
		struct nvif_perfdom_read_v0 v0;
	} *args = data;
	struct nvkm_object *object = &dom->object;
	struct nvkm_pm *pm = dom->perfmon->pm;
	int ret = -ENOSYS, i;

	nvif_ioctl(object, "perfdom read size %d\n", size);
	if (!(ret = nvif_unpack(ret, &data, &size, args->v0, 0, 0, false))) {
		nvif_ioctl(object, "perfdom read vers %d\n", args->v0.version);
	} else
		return ret;

	for (i = 0; i < 4; i++) {
		if (dom->ctr[i])
			dom->func->read(pm, dom, dom->ctr[i]);
	}

	if (!dom->clk)
		return -EAGAIN;

	for (i = 0; i < 4; i++)
		if (dom->ctr[i])
			args->v0.ctr[i] = dom->ctr[i]->ctr;
	args->v0.clk = dom->clk;
	return 0;
}