#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_7__ {int /*<<< orphan*/ * data; } ;
struct TYPE_6__ {int /*<<< orphan*/ * data; } ;
struct TYPE_9__ {struct nvkm_device* device; } ;
struct TYPE_10__ {TYPE_4__ subdev; } ;
struct nvkm_falcon {TYPE_2__ code; TYPE_1__ data; scalar_t__ external; int /*<<< orphan*/  core; scalar_t__ addr; TYPE_5__ engine; } ;
struct TYPE_8__ {int /*<<< orphan*/  index; } ;
struct nvkm_engine {TYPE_3__ subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 struct nvkm_falcon* nvkm_falcon (struct nvkm_engine*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,scalar_t__ const,int,int) ; 
 scalar_t__ nvkm_mc_enabled (struct nvkm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_memory_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,scalar_t__ const,int) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nvkm_falcon_fini(struct nvkm_engine *engine, bool suspend)
{
	struct nvkm_falcon *falcon = nvkm_falcon(engine);
	struct nvkm_device *device = falcon->engine.subdev.device;
	const u32 base = falcon->addr;

	if (!suspend) {
		nvkm_memory_unref(&falcon->core);
		if (falcon->external) {
			vfree(falcon->data.data);
			vfree(falcon->code.data);
			falcon->code.data = NULL;
		}
	}

	if (nvkm_mc_enabled(device, engine->subdev.index)) {
		nvkm_mask(device, base + 0x048, 0x00000003, 0x00000000);
		nvkm_wr32(device, base + 0x014, 0xffffffff);
	}
	return 0;
}