#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct nouveau_display {struct drm_property* color_vibrance_property; struct drm_property* vibrant_hue_property; struct drm_property* dithering_depth; struct drm_property* dithering_mode; struct drm_property* underscan_vborder_property; struct drm_property* underscan_hborder_property; struct drm_property* underscan_property; } ;
struct TYPE_10__ {int /*<<< orphan*/  color_vibrance; int /*<<< orphan*/  vibrant_hue; } ;
struct TYPE_9__ {int /*<<< orphan*/  depth; int /*<<< orphan*/  mode; } ;
struct TYPE_7__ {int /*<<< orphan*/  vborder; int /*<<< orphan*/  hborder; int /*<<< orphan*/  mode; } ;
struct TYPE_8__ {TYPE_2__ underscan; int /*<<< orphan*/  mode; } ;
struct nouveau_conn_atom {TYPE_5__ procamp; TYPE_4__ dither; TYPE_3__ scaler; } ;
struct drm_property {int dummy; } ;
struct TYPE_6__ {struct drm_property* scaling_mode_property; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct drm_connector_state {int dummy; } ;
struct drm_connector {struct drm_device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 struct nouveau_conn_atom* nouveau_conn_atom (struct drm_connector_state const*) ; 
 struct nouveau_display* nouveau_display (struct drm_device*) ; 

int
nouveau_conn_atomic_get_property(struct drm_connector *connector,
				 const struct drm_connector_state *state,
				 struct drm_property *property, u64 *val)
{
	struct nouveau_conn_atom *asyc = nouveau_conn_atom(state);
	struct nouveau_display *disp = nouveau_display(connector->dev);
	struct drm_device *dev = connector->dev;

	if (property == dev->mode_config.scaling_mode_property)
		*val = asyc->scaler.mode;
	else if (property == disp->underscan_property)
		*val = asyc->scaler.underscan.mode;
	else if (property == disp->underscan_hborder_property)
		*val = asyc->scaler.underscan.hborder;
	else if (property == disp->underscan_vborder_property)
		*val = asyc->scaler.underscan.vborder;
	else if (property == disp->dithering_mode)
		*val = asyc->dither.mode;
	else if (property == disp->dithering_depth)
		*val = asyc->dither.depth;
	else if (property == disp->vibrant_hue_property)
		*val = asyc->procamp.vibrant_hue;
	else if (property == disp->color_vibrance_property)
		*val = asyc->procamp.color_vibrance;
	else
		return -EINVAL;

	return 0;
}