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
typedef  enum nvkm_memory_target { ____Placeholder_nvkm_memory_target } nvkm_memory_target ;

/* Variables and functions */
 int EINVAL ; 
#define  NVKM_MEM_TARGET_HOST 130 
#define  NVKM_MEM_TARGET_NCOH 129 
#define  NVKM_MEM_TARGET_VRAM 128 

int
gf100_vmm_aper(enum nvkm_memory_target target)
{
	switch (target) {
	case NVKM_MEM_TARGET_VRAM: return 0;
	case NVKM_MEM_TARGET_HOST: return 2;
	case NVKM_MEM_TARGET_NCOH: return 3;
	default:
		return -EINVAL;
	}
}