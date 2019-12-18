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
struct nvkm_udevice {int /*<<< orphan*/  device; } ;
struct nvkm_oclass {struct nvkm_device_oclass* priv; int /*<<< orphan*/  parent; } ;
struct nvkm_object {int dummy; } ;
struct nvkm_device_oclass {int (* ctor ) (int /*<<< orphan*/ ,struct nvkm_oclass const*,void*,int /*<<< orphan*/ ,struct nvkm_object**) ;} ;

/* Variables and functions */
 struct nvkm_udevice* nvkm_udevice (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,struct nvkm_oclass const*,void*,int /*<<< orphan*/ ,struct nvkm_object**) ; 

__attribute__((used)) static int
nvkm_udevice_child_new(const struct nvkm_oclass *oclass,
		       void *data, u32 size, struct nvkm_object **pobject)
{
	struct nvkm_udevice *udev = nvkm_udevice(oclass->parent);
	const struct nvkm_device_oclass *sclass = oclass->priv;
	return sclass->ctor(udev->device, oclass, data, size, pobject);
}