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
struct drm_simple_display_pipe_funcs {int dummy; } ;
struct drm_crtc {int dummy; } ;
struct drm_plane {int dummy; } ;
struct drm_encoder {int /*<<< orphan*/  possible_crtcs; } ;
struct drm_simple_display_pipe {struct drm_simple_display_pipe_funcs const* funcs; struct drm_connector* connector; struct drm_crtc crtc; struct drm_plane plane; struct drm_encoder encoder; } ;
struct drm_device {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ENCODER_NONE ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_PRIMARY ; 
 int drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_crtc_helper_add (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int drm_crtc_init_with_planes (struct drm_device*,struct drm_crtc*,struct drm_plane*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_mask (struct drm_crtc*) ; 
 int drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_plane_helper_add (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_simple_kms_crtc_funcs ; 
 int /*<<< orphan*/  drm_simple_kms_crtc_helper_funcs ; 
 int /*<<< orphan*/  drm_simple_kms_encoder_funcs ; 
 int /*<<< orphan*/  drm_simple_kms_plane_funcs ; 
 int /*<<< orphan*/  drm_simple_kms_plane_helper_funcs ; 
 int drm_universal_plane_init (struct drm_device*,struct drm_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int drm_simple_display_pipe_init(struct drm_device *dev,
			struct drm_simple_display_pipe *pipe,
			const struct drm_simple_display_pipe_funcs *funcs,
			const uint32_t *formats, unsigned int format_count,
			const uint64_t *format_modifiers,
			struct drm_connector *connector)
{
	struct drm_encoder *encoder = &pipe->encoder;
	struct drm_plane *plane = &pipe->plane;
	struct drm_crtc *crtc = &pipe->crtc;
	int ret;

	pipe->connector = connector;
	pipe->funcs = funcs;

	drm_plane_helper_add(plane, &drm_simple_kms_plane_helper_funcs);
	ret = drm_universal_plane_init(dev, plane, 0,
				       &drm_simple_kms_plane_funcs,
				       formats, format_count,
				       format_modifiers,
				       DRM_PLANE_TYPE_PRIMARY, NULL);
	if (ret)
		return ret;

	drm_crtc_helper_add(crtc, &drm_simple_kms_crtc_helper_funcs);
	ret = drm_crtc_init_with_planes(dev, crtc, plane, NULL,
					&drm_simple_kms_crtc_funcs, NULL);
	if (ret)
		return ret;

	encoder->possible_crtcs = drm_crtc_mask(crtc);
	ret = drm_encoder_init(dev, encoder, &drm_simple_kms_encoder_funcs,
			       DRM_MODE_ENCODER_NONE, NULL);
	if (ret || !connector)
		return ret;

	return drm_connector_attach_encoder(connector, encoder);
}