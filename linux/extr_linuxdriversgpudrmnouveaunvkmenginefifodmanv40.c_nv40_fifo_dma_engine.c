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
typedef  int u32 ;
struct TYPE_4__ {int index; TYPE_1__* device; } ;
struct nvkm_engine {TYPE_2__ subdev; } ;
struct TYPE_3__ {int chipset; } ;

/* Variables and functions */
#define  NVKM_ENGINE_DMAOBJ 131 
#define  NVKM_ENGINE_GR 130 
#define  NVKM_ENGINE_MPEG 129 
#define  NVKM_ENGINE_SW 128 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static bool
nv40_fifo_dma_engine(struct nvkm_engine *engine, u32 *reg, u32 *ctx)
{
	switch (engine->subdev.index) {
	case NVKM_ENGINE_DMAOBJ:
	case NVKM_ENGINE_SW:
		return false;
	case NVKM_ENGINE_GR:
		*reg = 0x0032e0;
		*ctx = 0x38;
		return true;
	case NVKM_ENGINE_MPEG:
		if (engine->subdev.device->chipset < 0x44)
			return false;
		*reg = 0x00330c;
		*ctx = 0x54;
		return true;
	default:
		WARN_ON(1);
		return false;
	}
}