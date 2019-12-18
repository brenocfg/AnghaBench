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
struct ramfuc {struct nvkm_fb* fb; int /*<<< orphan*/  sequence; int /*<<< orphan*/  memx; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct nvkm_fb {TYPE_2__ subdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  pmu; } ;

/* Variables and functions */
 int nvkm_memx_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
ramfuc_init(struct ramfuc *ram, struct nvkm_fb *fb)
{
	int ret = nvkm_memx_init(fb->subdev.device->pmu, &ram->memx);
	if (ret)
		return ret;

	ram->sequence++;
	ram->fb = fb;
	return 0;
}