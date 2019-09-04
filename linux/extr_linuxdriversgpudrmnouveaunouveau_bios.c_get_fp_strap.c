#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nvif_object {int dummy; } ;
struct nvbios {int major_version; int* data; } ;
struct TYPE_4__ {scalar_t__ family; } ;
struct TYPE_6__ {TYPE_1__ info; struct nvif_object object; } ;
struct TYPE_5__ {TYPE_3__ device; } ;
struct nouveau_drm {TYPE_2__ client; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int NVReadVgaCrtc5758 (struct drm_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ NV_DEVICE_INFO_V0_MAXWELL ; 
 scalar_t__ NV_DEVICE_INFO_V0_TESLA ; 
 int NV_PEXTDEV_BOOT_0 ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int nvif_rd32 (struct nvif_object*,int) ; 

__attribute__((used)) static int
get_fp_strap(struct drm_device *dev, struct nvbios *bios)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nvif_object *device = &drm->client.device.object;

	/*
	 * The fp strap is normally dictated by the "User Strap" in
	 * PEXTDEV_BOOT_0[20:16], but on BMP cards when bit 2 of the
	 * Internal_Flags struct at 0x48 is set, the user strap gets overriden
	 * by the PCI subsystem ID during POST, but not before the previous user
	 * strap has been committed to CR58 for CR57=0xf on head A, which may be
	 * read and used instead
	 */

	if (bios->major_version < 5 && bios->data[0x48] & 0x4)
		return NVReadVgaCrtc5758(dev, 0, 0xf) & 0xf;

	if (drm->client.device.info.family >= NV_DEVICE_INFO_V0_MAXWELL)
		return nvif_rd32(device, 0x001800) & 0x0000000f;
	else
	if (drm->client.device.info.family >= NV_DEVICE_INFO_V0_TESLA)
		return (nvif_rd32(device, NV_PEXTDEV_BOOT_0) >> 24) & 0xf;
	else
		return (nvif_rd32(device, NV_PEXTDEV_BOOT_0) >> 16) & 0xf;
}