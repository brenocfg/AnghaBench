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
struct nvkm_gpuobj {int dummy; } ;

/* Variables and functions */
 int nvkm_ro32 (struct nvkm_gpuobj*,int) ; 

void
nvkm_gpuobj_memcpy_from(void *dst, struct nvkm_gpuobj *src, u32 srcoffset,
			u32 length)
{
	int i;

	for (i = 0; i < length; i += 4)
		((u32 *)src)[i / 4] = nvkm_ro32(src, srcoffset + i);
}