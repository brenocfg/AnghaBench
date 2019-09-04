#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct omap_plane {int /*<<< orphan*/  id; } ;
struct omap_drm_private {int /*<<< orphan*/  dispc; TYPE_1__* dispc_ops; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {scalar_t__ type; TYPE_3__* state; TYPE_2__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  zpos; int /*<<< orphan*/  rotation; } ;
struct TYPE_5__ {struct omap_drm_private* dev_private; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* ovl_enable ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ROTATE_0 ; 
 scalar_t__ DRM_PLANE_TYPE_PRIMARY ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct omap_plane* to_omap_plane (struct drm_plane*) ; 

__attribute__((used)) static void omap_plane_atomic_disable(struct drm_plane *plane,
				      struct drm_plane_state *old_state)
{
	struct omap_drm_private *priv = plane->dev->dev_private;
	struct omap_plane *omap_plane = to_omap_plane(plane);

	plane->state->rotation = DRM_MODE_ROTATE_0;
	plane->state->zpos = plane->type == DRM_PLANE_TYPE_PRIMARY
			   ? 0 : omap_plane->id;

	priv->dispc_ops->ovl_enable(priv->dispc, omap_plane->id, false);
}