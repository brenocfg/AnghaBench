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
typedef  int /*<<< orphan*/  u64 ;
struct omap_drm_private {struct drm_property* zorder_prop; } ;
struct drm_property {int dummy; } ;
struct drm_plane_state {int /*<<< orphan*/  zpos; } ;
struct drm_plane {TYPE_1__* dev; } ;
struct TYPE_2__ {struct omap_drm_private* dev_private; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int omap_plane_atomic_get_property(struct drm_plane *plane,
					  const struct drm_plane_state *state,
					  struct drm_property *property,
					  u64 *val)
{
	struct omap_drm_private *priv = plane->dev->dev_private;

	if (property == priv->zorder_prop)
		*val = state->zpos;
	else
		return -EINVAL;

	return 0;
}