#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  base; } ;
struct TYPE_12__ {void* saturation; void* hue; void* brightness; void* contrast; void* colorkey; } ;
struct nouveau_plane {int colorkey; int contrast; int brightness; int hue; int saturation; TYPE_5__ base; int /*<<< orphan*/  (* set_params ) (struct nouveau_plane*) ;int /*<<< orphan*/  color_encoding; TYPE_4__ props; } ;
struct TYPE_9__ {int chipset; } ;
struct TYPE_10__ {TYPE_1__ info; } ;
struct TYPE_11__ {TYPE_2__ device; } ;
struct nouveau_drm {TYPE_3__ client; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_BT601 ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_BT709 ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_LIMITED_RANGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*) ; 
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  drm_plane_cleanup (TYPE_5__*) ; 
 int /*<<< orphan*/  drm_plane_create_color_properties (TYPE_5__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_plane_force_disable (TYPE_5__*) ; 
 int drm_plane_init (struct drm_device*,TYPE_5__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int) ; 
 void* drm_property_create_range (struct drm_device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  formats ; 
 int /*<<< orphan*/  kfree (struct nouveau_plane*) ; 
 struct nouveau_plane* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nv10_plane_funcs ; 
 int /*<<< orphan*/  nv10_set_params (struct nouveau_plane*) ; 

__attribute__((used)) static void
nv10_overlay_init(struct drm_device *device)
{
	struct nouveau_drm *drm = nouveau_drm(device);
	struct nouveau_plane *plane = kzalloc(sizeof(struct nouveau_plane), GFP_KERNEL);
	unsigned int num_formats = ARRAY_SIZE(formats);
	int ret;

	if (!plane)
		return;

	switch (drm->client.device.info.chipset) {
	case 0x10:
	case 0x11:
	case 0x15:
	case 0x1a:
	case 0x20:
		num_formats = 2;
		break;
	}

	ret = drm_plane_init(device, &plane->base, 3 /* both crtc's */,
			     &nv10_plane_funcs,
			     formats, num_formats, false);
	if (ret)
		goto err;

	/* Set up the plane properties */
	plane->props.colorkey = drm_property_create_range(
			device, 0, "colorkey", 0, 0x01ffffff);
	plane->props.contrast = drm_property_create_range(
			device, 0, "contrast", 0, 8192 - 1);
	plane->props.brightness = drm_property_create_range(
			device, 0, "brightness", 0, 1024);
	plane->props.hue = drm_property_create_range(
			device, 0, "hue", 0, 359);
	plane->props.saturation = drm_property_create_range(
			device, 0, "saturation", 0, 8192 - 1);
	if (!plane->props.colorkey ||
	    !plane->props.contrast ||
	    !plane->props.brightness ||
	    !plane->props.hue ||
	    !plane->props.saturation)
		goto cleanup;

	plane->colorkey = 0;
	drm_object_attach_property(&plane->base.base,
				   plane->props.colorkey, plane->colorkey);

	plane->contrast = 0x1000;
	drm_object_attach_property(&plane->base.base,
				   plane->props.contrast, plane->contrast);

	plane->brightness = 512;
	drm_object_attach_property(&plane->base.base,
				   plane->props.brightness, plane->brightness);

	plane->hue = 0;
	drm_object_attach_property(&plane->base.base,
				   plane->props.hue, plane->hue);

	plane->saturation = 0x1000;
	drm_object_attach_property(&plane->base.base,
				   plane->props.saturation, plane->saturation);

	plane->color_encoding = DRM_COLOR_YCBCR_BT601;
	drm_plane_create_color_properties(&plane->base,
					  BIT(DRM_COLOR_YCBCR_BT601) |
					  BIT(DRM_COLOR_YCBCR_BT709),
					  BIT(DRM_COLOR_YCBCR_LIMITED_RANGE),
					  DRM_COLOR_YCBCR_BT601,
					  DRM_COLOR_YCBCR_LIMITED_RANGE);

	plane->set_params = nv10_set_params;
	nv10_set_params(plane);
	drm_plane_force_disable(&plane->base);
	return;
cleanup:
	drm_plane_cleanup(&plane->base);
err:
	kfree(plane);
	NV_ERROR(drm, "Failed to create plane\n");
}