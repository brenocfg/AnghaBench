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
struct nvkm_volt {int vid_nr; TYPE_1__* vid; TYPE_2__* func; } ;
struct TYPE_4__ {int (* volt_get ) (struct nvkm_volt*) ;int (* vid_get ) (struct nvkm_volt*) ;} ;
struct TYPE_3__ {int vid; int uv; } ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct nvkm_volt*) ; 
 int stub2 (struct nvkm_volt*) ; 

int
nvkm_volt_get(struct nvkm_volt *volt)
{
	int ret, i;

	if (volt->func->volt_get)
		return volt->func->volt_get(volt);

	ret = volt->func->vid_get(volt);
	if (ret >= 0) {
		for (i = 0; i < volt->vid_nr; i++) {
			if (volt->vid[i].vid == ret)
				return volt->vid[i].uv;
		}
		ret = -EINVAL;
	}
	return ret;
}