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
struct TYPE_6__ {int mthd; int size; int* data; } ;
struct nvkm_memx {TYPE_3__ c; TYPE_2__* pmu; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
memx_out(struct nvkm_memx *memx)
{
	struct nvkm_device *device = memx->pmu->subdev.device;
	int i;

	if (memx->c.mthd) {
		nvkm_wr32(device, 0x10a1c4, (memx->c.size << 16) | memx->c.mthd);
		for (i = 0; i < memx->c.size; i++)
			nvkm_wr32(device, 0x10a1c4, memx->c.data[i]);
		memx->c.mthd = 0;
		memx->c.size = 0;
	}
}