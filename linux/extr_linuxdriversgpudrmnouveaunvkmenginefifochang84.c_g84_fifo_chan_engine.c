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
#define  NVKM_ENGINE_BSP 137 
#define  NVKM_ENGINE_CE0 136 
#define  NVKM_ENGINE_CIPHER 135 
#define  NVKM_ENGINE_GR 134 
#define  NVKM_ENGINE_MPEG 133 
#define  NVKM_ENGINE_MSPDEC 132 
#define  NVKM_ENGINE_MSPPP 131 
#define  NVKM_ENGINE_MSVLD 130 
#define  NVKM_ENGINE_SEC 129 
#define  NVKM_ENGINE_VP 128 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static int
g84_fifo_chan_engine(struct nvkm_engine *engine)
{
	switch (engine->subdev.index) {
	case NVKM_ENGINE_GR    : return 0;
	case NVKM_ENGINE_MPEG  :
	case NVKM_ENGINE_MSPPP : return 1;
	case NVKM_ENGINE_CE0   : return 2;
	case NVKM_ENGINE_VP    :
	case NVKM_ENGINE_MSPDEC: return 3;
	case NVKM_ENGINE_CIPHER:
	case NVKM_ENGINE_SEC   : return 4;
	case NVKM_ENGINE_BSP   :
	case NVKM_ENGINE_MSVLD : return 5;
	default:
		WARN_ON(1);
		return 0;
	}
}