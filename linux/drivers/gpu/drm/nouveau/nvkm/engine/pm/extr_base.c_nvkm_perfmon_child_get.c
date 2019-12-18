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
struct TYPE_2__ {scalar_t__ maxver; scalar_t__ minver; int /*<<< orphan*/  oclass; } ;
struct nvkm_oclass {int /*<<< orphan*/  ctor; TYPE_1__ base; } ;
struct nvkm_object {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NVIF_CLASS_PERFDOM ; 
 int /*<<< orphan*/  nvkm_perfmon_child_new ; 

__attribute__((used)) static int
nvkm_perfmon_child_get(struct nvkm_object *object, int index,
		       struct nvkm_oclass *oclass)
{
	if (index == 0) {
		oclass->base.oclass = NVIF_CLASS_PERFDOM;
		oclass->base.minver = 0;
		oclass->base.maxver = 0;
		oclass->ctor = nvkm_perfmon_child_new;
		return 0;
	}
	return -EINVAL;
}