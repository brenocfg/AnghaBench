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
typedef  int u32 ;
struct TYPE_2__ {int index; } ;
struct nvkm_engine {TYPE_1__ subdev; } ;

/* Variables and functions */
#define  NVKM_ENGINE_CE0 134 
#define  NVKM_ENGINE_CE1 133 
#define  NVKM_ENGINE_GR 132 
#define  NVKM_ENGINE_MSPDEC 131 
#define  NVKM_ENGINE_MSPPP 130 
#define  NVKM_ENGINE_MSVLD 129 
#define  NVKM_ENGINE_SW 128 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static u32
gf100_fifo_gpfifo_engine_addr(struct nvkm_engine *engine)
{
	switch (engine->subdev.index) {
	case NVKM_ENGINE_SW    : return 0;
	case NVKM_ENGINE_GR    : return 0x0210;
	case NVKM_ENGINE_CE0   : return 0x0230;
	case NVKM_ENGINE_CE1   : return 0x0240;
	case NVKM_ENGINE_MSPDEC: return 0x0250;
	case NVKM_ENGINE_MSPPP : return 0x0260;
	case NVKM_ENGINE_MSVLD : return 0x0270;
	default:
		WARN_ON(1);
		return 0;
	}
}