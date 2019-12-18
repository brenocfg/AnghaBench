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
typedef  scalar_t__ u32 ;
struct nvkm_gpuobj {scalar_t__ map; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32_native (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
nvkm_gpuobj_wr32_fast(struct nvkm_gpuobj *gpuobj, u32 offset, u32 data)
{
	iowrite32_native(data, gpuobj->map + offset);
}