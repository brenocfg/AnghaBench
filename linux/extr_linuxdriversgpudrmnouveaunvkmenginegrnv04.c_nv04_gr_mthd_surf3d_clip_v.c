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

/* Variables and functions */
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static bool
nv04_gr_mthd_surf3d_clip_v(struct nvkm_device *device, u32 inst, u32 data)
{
	u32 min = data & 0xffff, max;
	u32 w = data >> 16;
	if (min & 0x8000)
		/* too large */
		return false;
	if (w & 0x8000)
		/* yes, it accepts negative for some reason. */
		w |= 0xffff0000;
	max = min + w;
	max &= 0x3ffff;
	nvkm_wr32(device, 0x400540, min);
	nvkm_wr32(device, 0x400548, max);
	return true;
}