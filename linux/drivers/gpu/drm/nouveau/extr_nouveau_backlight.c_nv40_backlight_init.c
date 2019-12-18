#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nvif_object {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {TYPE_1__ base; } ;
struct nouveau_encoder {TYPE_2__ base; } ;
struct TYPE_7__ {struct nvif_object object; } ;
struct TYPE_8__ {TYPE_3__ device; } ;
struct nouveau_drm {TYPE_4__ client; } ;
struct backlight_properties {int max_brightness; int /*<<< orphan*/  type; } ;
struct backlight_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 int ENODEV ; 
 int /*<<< orphan*/  NV40_PMC_BACKLIGHT ; 
 int NV40_PMC_BACKLIGHT_MASK ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 
 struct backlight_ops nv40_bl_ops ; 
 int nvif_rd32 (struct nvif_object*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv40_backlight_init(struct nouveau_encoder *encoder,
		    struct backlight_properties *props,
		    const struct backlight_ops **ops)
{
	struct nouveau_drm *drm = nouveau_drm(encoder->base.base.dev);
	struct nvif_object *device = &drm->client.device.object;

	if (!(nvif_rd32(device, NV40_PMC_BACKLIGHT) & NV40_PMC_BACKLIGHT_MASK))
		return -ENODEV;

	props->type = BACKLIGHT_RAW;
	props->max_brightness = 31;
	*ops = &nv40_bl_ops;
	return 0;
}