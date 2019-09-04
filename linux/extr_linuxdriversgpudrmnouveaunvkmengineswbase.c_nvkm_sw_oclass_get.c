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
struct nvkm_sw {TYPE_3__* func; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctor; } ;
struct nvkm_oclass {TYPE_1__ base; TYPE_2__* engn; int /*<<< orphan*/  engine; } ;
struct TYPE_6__ {TYPE_2__* sclass; } ;
struct TYPE_5__ {TYPE_1__ base; scalar_t__ ctor; } ;

/* Variables and functions */
 struct nvkm_sw* nvkm_sw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_sw_oclass_new ; 

__attribute__((used)) static int
nvkm_sw_oclass_get(struct nvkm_oclass *oclass, int index)
{
	struct nvkm_sw *sw = nvkm_sw(oclass->engine);
	int c = 0;

	while (sw->func->sclass[c].ctor) {
		if (c++ == index) {
			oclass->engn = &sw->func->sclass[index];
			oclass->base =  sw->func->sclass[index].base;
			oclass->base.ctor = nvkm_sw_oclass_new;
			return index;
		}
	}

	return c;
}