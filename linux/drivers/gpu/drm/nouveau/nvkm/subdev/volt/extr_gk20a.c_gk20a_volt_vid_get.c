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
struct nvkm_volt {int dummy; } ;
struct TYPE_4__ {int vid_nr; TYPE_1__* vid; } ;
struct gk20a_volt {TYPE_2__ base; int /*<<< orphan*/  vdd; } ;
struct TYPE_3__ {int uv; } ;

/* Variables and functions */
 int EINVAL ; 
 struct gk20a_volt* gk20a_volt (struct nvkm_volt*) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gk20a_volt_vid_get(struct nvkm_volt *base)
{
	struct gk20a_volt *volt = gk20a_volt(base);
	int i, uv;

	uv = regulator_get_voltage(volt->vdd);

	for (i = 0; i < volt->base.vid_nr; i++)
		if (volt->base.vid[i].uv >= uv)
			return i;

	return -EINVAL;
}