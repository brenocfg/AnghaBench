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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_gpuobj {int /*<<< orphan*/  memory; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_ro32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
nvkm_gpuobj_heap_rd32(struct nvkm_gpuobj *gpuobj, u32 offset)
{
	return nvkm_ro32(gpuobj->memory, offset);
}