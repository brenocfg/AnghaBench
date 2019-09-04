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
typedef  int u64 ;
struct nvkm_memory {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mn; } ;

/* Variables and functions */
 int NVKM_RAM_MM_SHIFT ; 
 scalar_t__ nvkm_mm_size (int /*<<< orphan*/ ) ; 
 TYPE_1__* nvkm_vram (struct nvkm_memory*) ; 

__attribute__((used)) static u64
nvkm_vram_size(struct nvkm_memory *memory)
{
	return (u64)nvkm_mm_size(nvkm_vram(memory)->mn) << NVKM_RAM_MM_SHIFT;
}