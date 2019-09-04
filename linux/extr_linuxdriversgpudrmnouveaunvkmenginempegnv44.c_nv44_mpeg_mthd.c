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
 int nv40_mpeg_mthd_dma (struct nvkm_device*,int,int) ; 

__attribute__((used)) static bool
nv44_mpeg_mthd(struct nvkm_device *device, u32 mthd, u32 data)
{
	switch (mthd) {
	case 0x190:
	case 0x1a0:
	case 0x1b0:
		return nv40_mpeg_mthd_dma(device, mthd, data);
	default:
		break;
	}
	return false;
}