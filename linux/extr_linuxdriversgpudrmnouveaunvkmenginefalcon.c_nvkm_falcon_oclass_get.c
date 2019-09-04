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
struct TYPE_3__ {scalar_t__ oclass; } ;
struct nvkm_oclass {TYPE_1__ base; int /*<<< orphan*/  engine; } ;
struct nvkm_falcon {TYPE_2__* func; } ;
struct TYPE_4__ {TYPE_1__* sclass; } ;

/* Variables and functions */
 struct nvkm_falcon* nvkm_falcon (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvkm_falcon_oclass_get(struct nvkm_oclass *oclass, int index)
{
	struct nvkm_falcon *falcon = nvkm_falcon(oclass->engine);
	int c = 0;

	while (falcon->func->sclass[c].oclass) {
		if (c++ == index) {
			oclass->base = falcon->func->sclass[index];
			return index;
		}
	}

	return c;
}