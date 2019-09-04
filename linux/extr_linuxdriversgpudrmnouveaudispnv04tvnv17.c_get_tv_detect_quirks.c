#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct nvkm_device {TYPE_2__* quirk; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct nouveau_drm {TYPE_1__ client; } ;
struct drm_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ tv_pin_mask; } ;

/* Variables and functions */
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 struct nvkm_device* nvxx_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
get_tv_detect_quirks(struct drm_device *dev, uint32_t *pin_mask)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nvkm_device *device = nvxx_device(&drm->client.device);

	if (device->quirk && device->quirk->tv_pin_mask) {
		*pin_mask = device->quirk->tv_pin_mask;
		return false;
	}

	return true;
}