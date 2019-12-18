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
struct drm_encoder {int dummy; } ;
struct drm_display_mode {scalar_t__ hdisplay; scalar_t__ vdisplay; scalar_t__ vtotal; scalar_t__ htotal; scalar_t__ clock; } ;
struct ch7006_priv {int norm; } ;
struct TYPE_2__ {scalar_t__ clock; scalar_t__ hdisplay; scalar_t__ vdisplay; scalar_t__ vtotal; scalar_t__ htotal; } ;
struct ch7006_mode {int valid_norms; TYPE_1__ mode; } ;

/* Variables and functions */
 struct ch7006_mode* ch7006_modes ; 
 struct ch7006_priv* to_ch7006_priv (struct drm_encoder*) ; 

const struct ch7006_mode *ch7006_lookup_mode(struct drm_encoder *encoder,
					     const struct drm_display_mode *drm_mode)
{
	struct ch7006_priv *priv = to_ch7006_priv(encoder);
	const struct ch7006_mode *mode;

	for (mode = ch7006_modes; mode->mode.clock; mode++) {

		if (~mode->valid_norms & 1<<priv->norm)
			continue;

		if (mode->mode.hdisplay != drm_mode->hdisplay ||
		    mode->mode.vdisplay != drm_mode->vdisplay ||
		    mode->mode.vtotal != drm_mode->vtotal ||
		    mode->mode.htotal != drm_mode->htotal ||
		    mode->mode.clock != drm_mode->clock)
			continue;

		return mode;
	}

	return NULL;
}