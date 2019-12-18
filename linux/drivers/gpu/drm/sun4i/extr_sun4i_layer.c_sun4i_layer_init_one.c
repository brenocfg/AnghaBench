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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct sun4i_layer {int /*<<< orphan*/  plane; struct sun4i_backend* backend; } ;
struct sun4i_backend {int /*<<< orphan*/  frontend; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 struct sun4i_layer* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 scalar_t__ SUN4I_BACKEND_NUM_LAYERS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct sun4i_layer* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_plane_create_alpha_property (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_plane_create_zpos_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  drm_plane_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sun4i_backend_layer_formats ; 
 int /*<<< orphan*/  sun4i_backend_layer_funcs ; 
 int /*<<< orphan*/  sun4i_backend_layer_helper_funcs ; 
 int /*<<< orphan*/ * sun4i_layer_formats ; 
 int /*<<< orphan*/ * sun4i_layer_modifiers ; 

__attribute__((used)) static struct sun4i_layer *sun4i_layer_init_one(struct drm_device *drm,
						struct sun4i_backend *backend,
						enum drm_plane_type type)
{
	const uint64_t *modifiers = sun4i_layer_modifiers;
	const uint32_t *formats = sun4i_layer_formats;
	unsigned int formats_len = ARRAY_SIZE(sun4i_layer_formats);
	struct sun4i_layer *layer;
	int ret;

	layer = devm_kzalloc(drm->dev, sizeof(*layer), GFP_KERNEL);
	if (!layer)
		return ERR_PTR(-ENOMEM);

	layer->backend = backend;

	if (IS_ERR_OR_NULL(backend->frontend)) {
		formats = sun4i_backend_layer_formats;
		formats_len = ARRAY_SIZE(sun4i_backend_layer_formats);
		modifiers = NULL;
	}

	/* possible crtcs are set later */
	ret = drm_universal_plane_init(drm, &layer->plane, 0,
				       &sun4i_backend_layer_funcs,
				       formats, formats_len,
				       modifiers, type, NULL);
	if (ret) {
		dev_err(drm->dev, "Couldn't initialize layer\n");
		return ERR_PTR(ret);
	}

	drm_plane_helper_add(&layer->plane,
			     &sun4i_backend_layer_helper_funcs);

	drm_plane_create_alpha_property(&layer->plane);
	drm_plane_create_zpos_property(&layer->plane, 0, 0,
				       SUN4I_BACKEND_NUM_LAYERS - 1);

	return layer;
}