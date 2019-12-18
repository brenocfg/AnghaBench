#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int index; } ;
struct nvkm_engine {TYPE_1__ subdev; } ;

/* Variables and functions */
#define  NVKM_ENGINE_DMAOBJ 131 
#define  NVKM_ENGINE_GR 130 
#define  NVKM_ENGINE_MPEG 129 
#define  NVKM_ENGINE_SW 128 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static int
nv50_fifo_chan_engine_addr(struct nvkm_engine *engine)
{
	switch (engine->subdev.index) {
	case NVKM_ENGINE_DMAOBJ:
	case NVKM_ENGINE_SW    : return -1;
	case NVKM_ENGINE_GR    : return 0x0000;
	case NVKM_ENGINE_MPEG  : return 0x0060;
	default:
		WARN_ON(1);
		return -1;
	}
}