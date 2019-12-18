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
typedef  int uint64_t ;
struct drm_property {int dummy; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {TYPE_1__* dev; } ;
struct armada_private {struct drm_property* saturation_prop; struct drm_property* contrast_prop; struct drm_property* brightness_prop; struct drm_property* colorkey_mode_prop; struct drm_property* colorkey_alpha_prop; struct drm_property* colorkey_val_prop; struct drm_property* colorkey_max_prop; struct drm_property* colorkey_min_prop; struct drm_property* colorkey_prop; } ;
struct TYPE_4__ {int colorkey_mode; int brightness; int contrast; int saturation; int /*<<< orphan*/  colorkey_vb; int /*<<< orphan*/  colorkey_ug; int /*<<< orphan*/  colorkey_yr; } ;
struct TYPE_3__ {struct armada_private* dev_private; } ;

/* Variables and functions */
 int CFG_CKMODE_MASK ; 
 int EINVAL ; 
 int R2BGR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* drm_to_overlay_state (struct drm_plane_state const*) ; 
 int ffs (int) ; 

__attribute__((used)) static int armada_overlay_get_property(struct drm_plane *plane,
	const struct drm_plane_state *state, struct drm_property *property,
	uint64_t *val)
{
	struct armada_private *priv = plane->dev->dev_private;

#define C2K(c,s)	(((c) >> (s)) & 0xff)
#define R2BGR(r,g,b,s)	(C2K(r,s) << 0 | C2K(g,s) << 8 | C2K(b,s) << 16)
	if (property == priv->colorkey_prop) {
		/* Do best-efforts here for this property */
		*val = R2BGR(drm_to_overlay_state(state)->colorkey_yr,
			     drm_to_overlay_state(state)->colorkey_ug,
			     drm_to_overlay_state(state)->colorkey_vb, 16);
		/* If min != max, or min != val, error out */
		if (*val != R2BGR(drm_to_overlay_state(state)->colorkey_yr,
				  drm_to_overlay_state(state)->colorkey_ug,
				  drm_to_overlay_state(state)->colorkey_vb, 24) ||
		    *val != R2BGR(drm_to_overlay_state(state)->colorkey_yr,
				  drm_to_overlay_state(state)->colorkey_ug,
				  drm_to_overlay_state(state)->colorkey_vb, 8))
			return -EINVAL;
	} else if (property == priv->colorkey_min_prop) {
		*val = R2BGR(drm_to_overlay_state(state)->colorkey_yr,
			     drm_to_overlay_state(state)->colorkey_ug,
			     drm_to_overlay_state(state)->colorkey_vb, 16);
	} else if (property == priv->colorkey_max_prop) {
		*val = R2BGR(drm_to_overlay_state(state)->colorkey_yr,
			     drm_to_overlay_state(state)->colorkey_ug,
			     drm_to_overlay_state(state)->colorkey_vb, 24);
	} else if (property == priv->colorkey_val_prop) {
		*val = R2BGR(drm_to_overlay_state(state)->colorkey_yr,
			     drm_to_overlay_state(state)->colorkey_ug,
			     drm_to_overlay_state(state)->colorkey_vb, 8);
	} else if (property == priv->colorkey_alpha_prop) {
		*val = R2BGR(drm_to_overlay_state(state)->colorkey_yr,
			     drm_to_overlay_state(state)->colorkey_ug,
			     drm_to_overlay_state(state)->colorkey_vb, 0);
	} else if (property == priv->colorkey_mode_prop) {
		*val = (drm_to_overlay_state(state)->colorkey_mode &
			CFG_CKMODE_MASK) >> ffs(CFG_CKMODE_MASK);
	} else if (property == priv->brightness_prop) {
		*val = drm_to_overlay_state(state)->brightness + 256;
	} else if (property == priv->contrast_prop) {
		*val = drm_to_overlay_state(state)->contrast;
	} else if (property == priv->saturation_prop) {
		*val = drm_to_overlay_state(state)->saturation;
	} else {
		return -EINVAL;
	}
	return 0;
}