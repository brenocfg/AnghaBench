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
struct nvif_object {int dummy; } ;
struct TYPE_3__ {struct nvif_object object; } ;
struct TYPE_4__ {TYPE_1__ device; } ;
struct nouveau_drm {TYPE_2__ client; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV40_PMC_BACKLIGHT ; 
 int NV40_PMC_BACKLIGHT_MASK ; 
 struct nouveau_drm* bl_get_data (struct backlight_device*) ; 
 int nvif_rd32 (struct nvif_object*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv40_get_intensity(struct backlight_device *bd)
{
	struct nouveau_drm *drm = bl_get_data(bd);
	struct nvif_object *device = &drm->client.device.object;
	int val = (nvif_rd32(device, NV40_PMC_BACKLIGHT) &
				   NV40_PMC_BACKLIGHT_MASK) >> 16;

	return val;
}