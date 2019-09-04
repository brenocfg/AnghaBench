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
struct nvkm_engine {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;
struct gf100_fifo {TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVKM_ENGINE_CE0 ; 
 int /*<<< orphan*/  NVKM_ENGINE_CE1 ; 
 int /*<<< orphan*/  NVKM_ENGINE_GR ; 
 int /*<<< orphan*/  NVKM_ENGINE_MSPDEC ; 
 int /*<<< orphan*/  NVKM_ENGINE_MSPPP ; 
 int /*<<< orphan*/  NVKM_ENGINE_MSVLD ; 
 struct nvkm_engine* nvkm_device_engine (struct nvkm_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct nvkm_engine *
gf100_fifo_engine(struct gf100_fifo *fifo, u32 engn)
{
	struct nvkm_device *device = fifo->base.engine.subdev.device;

	switch (engn) {
	case 0: engn = NVKM_ENGINE_GR; break;
	case 1: engn = NVKM_ENGINE_MSVLD; break;
	case 2: engn = NVKM_ENGINE_MSPPP; break;
	case 3: engn = NVKM_ENGINE_MSPDEC; break;
	case 4: engn = NVKM_ENGINE_CE0; break;
	case 5: engn = NVKM_ENGINE_CE1; break;
	default:
		return NULL;
	}

	return nvkm_device_engine(device, engn);
}