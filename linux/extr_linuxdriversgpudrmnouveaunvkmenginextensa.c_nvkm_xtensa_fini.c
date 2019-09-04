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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;
struct nvkm_xtensa {int /*<<< orphan*/  gpu_fw; scalar_t__ addr; TYPE_2__ engine; } ;
struct nvkm_engine {int dummy; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_memory_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,scalar_t__ const,int /*<<< orphan*/ ) ; 
 struct nvkm_xtensa* nvkm_xtensa (struct nvkm_engine*) ; 

__attribute__((used)) static int
nvkm_xtensa_fini(struct nvkm_engine *engine, bool suspend)
{
	struct nvkm_xtensa *xtensa = nvkm_xtensa(engine);
	struct nvkm_device *device = xtensa->engine.subdev.device;
	const u32 base = xtensa->addr;

	nvkm_wr32(device, base + 0xd84, 0); /* INTR_EN */
	nvkm_wr32(device, base + 0xd94, 0); /* FIFO_CTRL */

	if (!suspend)
		nvkm_memory_unref(&xtensa->gpu_fw);
	return 0;
}