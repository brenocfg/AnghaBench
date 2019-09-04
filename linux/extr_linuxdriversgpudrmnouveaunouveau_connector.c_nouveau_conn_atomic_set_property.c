#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_10__ {int /*<<< orphan*/  oclass; } ;
struct TYPE_11__ {TYPE_2__ object; } ;
struct nouveau_display {struct drm_property* color_vibrance_property; struct drm_property* vibrant_hue_property; struct drm_property* dithering_depth; struct drm_property* dithering_mode; struct drm_property* underscan_vborder_property; struct drm_property* underscan_hborder_property; struct drm_property* underscan_property; TYPE_3__ disp; } ;
struct TYPE_16__ {int scaler; int dither; int procamp; } ;
struct TYPE_15__ {int vibrant_hue; int color_vibrance; } ;
struct TYPE_14__ {int mode; int depth; } ;
struct TYPE_12__ {int mode; int hborder; int vborder; } ;
struct TYPE_13__ {int mode; TYPE_4__ underscan; } ;
struct nouveau_conn_atom {TYPE_8__ set; TYPE_7__ procamp; TYPE_6__ dither; TYPE_5__ scaler; } ;
struct drm_property {int dummy; } ;
struct TYPE_9__ {struct drm_property* scaling_mode_property; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct drm_connector_state {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  connector_type; struct drm_device* dev; } ;

/* Variables and functions */
#define  DRM_MODE_CONNECTOR_LVDS 133 
#define  DRM_MODE_CONNECTOR_eDP 132 
#define  DRM_MODE_SCALE_ASPECT 131 
#define  DRM_MODE_SCALE_CENTER 130 
#define  DRM_MODE_SCALE_FULLSCREEN 129 
#define  DRM_MODE_SCALE_NONE 128 
 int EINVAL ; 
 int /*<<< orphan*/  NV50_DISP ; 
 struct nouveau_conn_atom* nouveau_conn_atom (struct drm_connector_state*) ; 
 struct nouveau_display* nouveau_display (struct drm_device*) ; 

int
nouveau_conn_atomic_set_property(struct drm_connector *connector,
				 struct drm_connector_state *state,
				 struct drm_property *property, u64 val)
{
	struct drm_device *dev = connector->dev;
	struct nouveau_conn_atom *asyc = nouveau_conn_atom(state);
	struct nouveau_display *disp = nouveau_display(dev);

	if (property == dev->mode_config.scaling_mode_property) {
		switch (val) {
		case DRM_MODE_SCALE_NONE:
			/* We allow 'None' for EDID modes, even on a fixed
			 * panel (some exist with support for lower refresh
			 * rates, which people might want to use for power-
			 * saving purposes).
			 *
			 * Non-EDID modes will force the use of GPU scaling
			 * to the native mode regardless of this setting.
			 */
			switch (connector->connector_type) {
			case DRM_MODE_CONNECTOR_LVDS:
			case DRM_MODE_CONNECTOR_eDP:
				/* ... except prior to G80, where the code
				 * doesn't support such things.
				 */
				if (disp->disp.object.oclass < NV50_DISP)
					return -EINVAL;
				break;
			default:
				break;
			}
		case DRM_MODE_SCALE_FULLSCREEN:
		case DRM_MODE_SCALE_CENTER:
		case DRM_MODE_SCALE_ASPECT:
			break;
		default:
			return -EINVAL;
		}

		if (asyc->scaler.mode != val) {
			asyc->scaler.mode = val;
			asyc->set.scaler = true;
		}
	} else
	if (property == disp->underscan_property) {
		if (asyc->scaler.underscan.mode != val) {
			asyc->scaler.underscan.mode = val;
			asyc->set.scaler = true;
		}
	} else
	if (property == disp->underscan_hborder_property) {
		if (asyc->scaler.underscan.hborder != val) {
			asyc->scaler.underscan.hborder = val;
			asyc->set.scaler = true;
		}
	} else
	if (property == disp->underscan_vborder_property) {
		if (asyc->scaler.underscan.vborder != val) {
			asyc->scaler.underscan.vborder = val;
			asyc->set.scaler = true;
		}
	} else
	if (property == disp->dithering_mode) {
		if (asyc->dither.mode != val) {
			asyc->dither.mode = val;
			asyc->set.dither = true;
		}
	} else
	if (property == disp->dithering_depth) {
		if (asyc->dither.mode != val) {
			asyc->dither.depth = val;
			asyc->set.dither = true;
		}
	} else
	if (property == disp->vibrant_hue_property) {
		if (asyc->procamp.vibrant_hue != val) {
			asyc->procamp.vibrant_hue = val;
			asyc->set.procamp = true;
		}
	} else
	if (property == disp->color_vibrance_property) {
		if (asyc->procamp.color_vibrance != val) {
			asyc->procamp.color_vibrance = val;
			asyc->set.procamp = true;
		}
	} else {
		return -EINVAL;
	}

	return 0;
}