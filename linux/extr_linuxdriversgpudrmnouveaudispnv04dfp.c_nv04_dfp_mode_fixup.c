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
struct drm_display_mode {scalar_t__ hdisplay; scalar_t__ vdisplay; int /*<<< orphan*/  clock; } ;
struct nouveau_encoder {struct drm_display_mode mode; } ;
struct nouveau_connector {scalar_t__ scaling_mode; struct drm_display_mode* native_mode; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 scalar_t__ DRM_MODE_SCALE_NONE ; 
 struct nouveau_encoder* nouveau_encoder (struct drm_encoder*) ; 
 struct nouveau_connector* nouveau_encoder_connector_get (struct nouveau_encoder*) ; 

__attribute__((used)) static bool nv04_dfp_mode_fixup(struct drm_encoder *encoder,
				const struct drm_display_mode *mode,
				struct drm_display_mode *adjusted_mode)
{
	struct nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	struct nouveau_connector *nv_connector = nouveau_encoder_connector_get(nv_encoder);

	if (!nv_connector->native_mode ||
	    nv_connector->scaling_mode == DRM_MODE_SCALE_NONE ||
	    mode->hdisplay > nv_connector->native_mode->hdisplay ||
	    mode->vdisplay > nv_connector->native_mode->vdisplay) {
		nv_encoder->mode = *adjusted_mode;

	} else {
		nv_encoder->mode = *nv_connector->native_mode;
		adjusted_mode->clock = nv_connector->native_mode->clock;
	}

	return true;
}