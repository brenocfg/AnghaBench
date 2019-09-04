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
struct nvkm_memory {int dummy; } ;
typedef  enum nvkm_memory_target { ____Placeholder_nvkm_memory_target } nvkm_memory_target ;

/* Variables and functions */
 int NVKM_MEM_TARGET_VRAM ; 

__attribute__((used)) static enum nvkm_memory_target
nvkm_vram_target(struct nvkm_memory *memory)
{
	return NVKM_MEM_TARGET_VRAM;
}