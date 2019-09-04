#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct gf100_fifo {int dummy; } ;

/* Variables and functions */
#define  NVKM_ENGINE_CE0 133 
#define  NVKM_ENGINE_CE1 132 
#define  NVKM_ENGINE_GR 131 
#define  NVKM_ENGINE_MSPDEC 130 
#define  NVKM_ENGINE_MSPPP 129 
#define  NVKM_ENGINE_MSVLD 128 

__attribute__((used)) static inline int
gf100_fifo_engidx(struct gf100_fifo *fifo, u32 engn)
{
	switch (engn) {
	case NVKM_ENGINE_GR    : engn = 0; break;
	case NVKM_ENGINE_MSVLD : engn = 1; break;
	case NVKM_ENGINE_MSPPP : engn = 2; break;
	case NVKM_ENGINE_MSPDEC: engn = 3; break;
	case NVKM_ENGINE_CE0   : engn = 4; break;
	case NVKM_ENGINE_CE1   : engn = 5; break;
	default:
		return -1;
	}

	return engn;
}