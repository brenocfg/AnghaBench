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
struct drm_connector {int interlace_allowed; int /*<<< orphan*/  base; } ;
struct vc4_vec_connector {struct vc4_vec* vec; int /*<<< orphan*/  encoder; struct drm_connector base; } ;
struct vc4_vec {int /*<<< orphan*/  encoder; int /*<<< orphan*/ * tv_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  tv_mode_property; } ;
struct drm_device {TYPE_1__ mode_config; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_Composite ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct drm_connector* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t VC4_VEC_TV_MODE_NTSC ; 
 struct vc4_vec_connector* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (struct drm_connector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  vc4_vec_connector_funcs ; 
 int /*<<< orphan*/  vc4_vec_connector_helper_funcs ; 
 int /*<<< orphan*/ * vc4_vec_tv_modes ; 

__attribute__((used)) static struct drm_connector *vc4_vec_connector_init(struct drm_device *dev,
						    struct vc4_vec *vec)
{
	struct drm_connector *connector = NULL;
	struct vc4_vec_connector *vec_connector;

	vec_connector = devm_kzalloc(dev->dev, sizeof(*vec_connector),
				     GFP_KERNEL);
	if (!vec_connector)
		return ERR_PTR(-ENOMEM);

	connector = &vec_connector->base;
	connector->interlace_allowed = true;

	vec_connector->encoder = vec->encoder;
	vec_connector->vec = vec;

	drm_connector_init(dev, connector, &vc4_vec_connector_funcs,
			   DRM_MODE_CONNECTOR_Composite);
	drm_connector_helper_add(connector, &vc4_vec_connector_helper_funcs);

	drm_object_attach_property(&connector->base,
				   dev->mode_config.tv_mode_property,
				   VC4_VEC_TV_MODE_NTSC);
	vec->tv_mode = &vc4_vec_tv_modes[VC4_VEC_TV_MODE_NTSC];

	drm_connector_attach_encoder(connector, vec->encoder);

	return connector;
}