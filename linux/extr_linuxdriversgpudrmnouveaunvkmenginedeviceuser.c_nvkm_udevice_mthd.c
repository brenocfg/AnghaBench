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
struct nvkm_udevice {int dummy; } ;
struct nvkm_object {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NV_DEVICE_V0_INFO 129 
#define  NV_DEVICE_V0_TIME 128 
 int /*<<< orphan*/  nvif_ioctl (struct nvkm_object*,char*,int) ; 
 struct nvkm_udevice* nvkm_udevice (struct nvkm_object*) ; 
 int nvkm_udevice_info (struct nvkm_udevice*,void*,int) ; 
 int nvkm_udevice_time (struct nvkm_udevice*,void*,int) ; 

__attribute__((used)) static int
nvkm_udevice_mthd(struct nvkm_object *object, u32 mthd, void *data, u32 size)
{
	struct nvkm_udevice *udev = nvkm_udevice(object);
	nvif_ioctl(object, "device mthd %08x\n", mthd);
	switch (mthd) {
	case NV_DEVICE_V0_INFO:
		return nvkm_udevice_info(udev, data, size);
	case NV_DEVICE_V0_TIME:
		return nvkm_udevice_time(udev, data, size);
	default:
		break;
	}
	return -EINVAL;
}