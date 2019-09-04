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
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_secboot {scalar_t__ wpr_size; int wpr_addr; struct nvkm_subdev subdev; } ;
struct nvkm_device {int dummy; } ;
struct acr_r352 {TYPE_1__* ls_blob; } ;
struct TYPE_2__ {int addr; int size; } ;

/* Variables and functions */
 int nvkm_rd32 (struct nvkm_device const*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device const*,int,int) ; 

__attribute__((used)) static bool
acr_r352_wpr_is_set(const struct acr_r352 *acr, const struct nvkm_secboot *sb)
{
	const struct nvkm_subdev *subdev = &sb->subdev;
	const struct nvkm_device *device = subdev->device;
	u64 wpr_lo, wpr_hi;
	u64 wpr_range_lo, wpr_range_hi;

	nvkm_wr32(device, 0x100cd4, 0x2);
	wpr_lo = (nvkm_rd32(device, 0x100cd4) & ~0xff);
	wpr_lo <<= 8;
	nvkm_wr32(device, 0x100cd4, 0x3);
	wpr_hi = (nvkm_rd32(device, 0x100cd4) & ~0xff);
	wpr_hi <<= 8;

	if (sb->wpr_size != 0) {
		wpr_range_lo = sb->wpr_addr;
		wpr_range_hi = wpr_range_lo + sb->wpr_size;
	} else {
		wpr_range_lo = acr->ls_blob->addr;
		wpr_range_hi = wpr_range_lo + acr->ls_blob->size;
	}

	return (wpr_lo >= wpr_range_lo && wpr_lo < wpr_range_hi &&
		wpr_hi > wpr_range_lo && wpr_hi <= wpr_range_hi);
}