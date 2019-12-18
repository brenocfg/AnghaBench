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
typedef  int /*<<< orphan*/  u64 ;
struct omap_drm_private {struct drm_property* zorder_prop; } ;
struct omap_crtc_state {int /*<<< orphan*/  zpos; int /*<<< orphan*/  rotation; } ;
struct drm_property {int dummy; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_2__* primary; TYPE_1__* dev; } ;
struct TYPE_4__ {struct drm_property* rotation_property; } ;
struct TYPE_3__ {struct omap_drm_private* dev_private; } ;

/* Variables and functions */
 int EINVAL ; 
 struct omap_crtc_state* to_omap_crtc_state (struct drm_crtc_state const*) ; 

__attribute__((used)) static int omap_crtc_atomic_get_property(struct drm_crtc *crtc,
					 const struct drm_crtc_state *state,
					 struct drm_property *property,
					 u64 *val)
{
	struct omap_drm_private *priv = crtc->dev->dev_private;
	struct omap_crtc_state *omap_state = to_omap_crtc_state(state);

	if (property == crtc->primary->rotation_property)
		*val = omap_state->rotation;
	else if (property == priv->zorder_prop)
		*val = omap_state->zpos;
	else
		return -EINVAL;

	return 0;
}