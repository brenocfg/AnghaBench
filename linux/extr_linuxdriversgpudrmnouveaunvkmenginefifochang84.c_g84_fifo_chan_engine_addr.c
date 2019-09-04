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
#define  NVKM_ENGINE_BSP 139 
#define  NVKM_ENGINE_CE0 138 
#define  NVKM_ENGINE_CIPHER 137 
#define  NVKM_ENGINE_DMAOBJ 136 
#define  NVKM_ENGINE_GR 135 
#define  NVKM_ENGINE_MPEG 134 
#define  NVKM_ENGINE_MSPDEC 133 
#define  NVKM_ENGINE_MSPPP 132 
#define  NVKM_ENGINE_MSVLD 131 
#define  NVKM_ENGINE_SEC 130 
#define  NVKM_ENGINE_SW 129 
#define  NVKM_ENGINE_VP 128 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static int
g84_fifo_chan_engine_addr(struct nvkm_engine *engine)
{
	switch (engine->subdev.index) {
	case NVKM_ENGINE_DMAOBJ:
	case NVKM_ENGINE_SW    : return -1;
	case NVKM_ENGINE_GR    : return 0x0020;
	case NVKM_ENGINE_VP    :
	case NVKM_ENGINE_MSPDEC: return 0x0040;
	case NVKM_ENGINE_MPEG  :
	case NVKM_ENGINE_MSPPP : return 0x0060;
	case NVKM_ENGINE_BSP   :
	case NVKM_ENGINE_MSVLD : return 0x0080;
	case NVKM_ENGINE_CIPHER:
	case NVKM_ENGINE_SEC   : return 0x00a0;
	case NVKM_ENGINE_CE0   : return 0x00c0;
	default:
		WARN_ON(1);
		return -1;
	}
}