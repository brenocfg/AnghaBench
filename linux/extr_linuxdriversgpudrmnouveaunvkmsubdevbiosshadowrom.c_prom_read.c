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
struct nvkm_device {int dummy; } ;
struct nvkm_bios {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int nvkm_rd32 (struct nvkm_device*,int) ; 

__attribute__((used)) static u32
prom_read(void *data, u32 offset, u32 length, struct nvkm_bios *bios)
{
	struct nvkm_device *device = data;
	u32 i;
	if (offset + length <= 0x00100000) {
		for (i = offset; i < offset + length; i += 4)
			*(u32 *)&bios->data[i] = nvkm_rd32(device, 0x300000 + i);
		return length;
	}
	return 0;
}