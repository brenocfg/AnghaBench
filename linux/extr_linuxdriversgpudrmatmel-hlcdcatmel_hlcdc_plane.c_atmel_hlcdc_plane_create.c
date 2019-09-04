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
struct drm_device {int /*<<< orphan*/  dev; struct atmel_hlcdc_dc* dev_private; } ;
struct atmel_hlcdc_plane {int /*<<< orphan*/  layer; int /*<<< orphan*/  base; } ;
struct atmel_hlcdc_layer_desc {scalar_t__ type; size_t id; TYPE_2__* formats; } ;
struct atmel_hlcdc_dc {int /*<<< orphan*/ ** layers; TYPE_1__* hlcdc; } ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;
struct TYPE_4__ {int /*<<< orphan*/  nformats; int /*<<< orphan*/  formats; } ;
struct TYPE_3__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 scalar_t__ ATMEL_HLCDC_BASE_LAYER ; 
 scalar_t__ ATMEL_HLCDC_CURSOR_LAYER ; 
 int DRM_PLANE_TYPE_CURSOR ; 
 int DRM_PLANE_TYPE_OVERLAY ; 
 int DRM_PLANE_TYPE_PRIMARY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atmel_hlcdc_layer_init (int /*<<< orphan*/ *,struct atmel_hlcdc_layer_desc const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_hlcdc_layer_plane_helper_funcs ; 
 int atmel_hlcdc_plane_init_properties (struct atmel_hlcdc_plane*) ; 
 struct atmel_hlcdc_plane* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_plane_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  layer_plane_funcs ; 

__attribute__((used)) static int atmel_hlcdc_plane_create(struct drm_device *dev,
				    const struct atmel_hlcdc_layer_desc *desc)
{
	struct atmel_hlcdc_dc *dc = dev->dev_private;
	struct atmel_hlcdc_plane *plane;
	enum drm_plane_type type;
	int ret;

	plane = devm_kzalloc(dev->dev, sizeof(*plane), GFP_KERNEL);
	if (!plane)
		return -ENOMEM;

	atmel_hlcdc_layer_init(&plane->layer, desc, dc->hlcdc->regmap);

	if (desc->type == ATMEL_HLCDC_BASE_LAYER)
		type = DRM_PLANE_TYPE_PRIMARY;
	else if (desc->type == ATMEL_HLCDC_CURSOR_LAYER)
		type = DRM_PLANE_TYPE_CURSOR;
	else
		type = DRM_PLANE_TYPE_OVERLAY;

	ret = drm_universal_plane_init(dev, &plane->base, 0,
				       &layer_plane_funcs,
				       desc->formats->formats,
				       desc->formats->nformats,
				       NULL, type, NULL);
	if (ret)
		return ret;

	drm_plane_helper_add(&plane->base,
			     &atmel_hlcdc_layer_plane_helper_funcs);

	/* Set default property values*/
	ret = atmel_hlcdc_plane_init_properties(plane);
	if (ret)
		return ret;

	dc->layers[desc->id] = &plane->layer;

	return 0;
}