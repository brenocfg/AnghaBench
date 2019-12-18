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
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {int id; int pipe; TYPE_2__ base; } ;
struct intel_crtc_state {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_1__ uncore; } ;
typedef  enum plane_id { ____Placeholder_plane_id } plane_id ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLANE_CTL (int,int) ; 
 int /*<<< orphan*/  PLANE_CUS_CTL (int,int) ; 
 int /*<<< orphan*/  PLANE_SURF (int,int) ; 
 scalar_t__ icl_is_hdr_plane (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  skl_write_plane_wm (struct intel_plane*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
skl_disable_plane(struct intel_plane *plane,
		  const struct intel_crtc_state *crtc_state)
{
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);
	enum plane_id plane_id = plane->id;
	enum pipe pipe = plane->pipe;
	unsigned long irqflags;

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	if (icl_is_hdr_plane(dev_priv, plane_id))
		I915_WRITE_FW(PLANE_CUS_CTL(pipe, plane_id), 0);

	skl_write_plane_wm(plane, crtc_state);

	I915_WRITE_FW(PLANE_CTL(pipe, plane_id), 0);
	I915_WRITE_FW(PLANE_SURF(pipe, plane_id), 0);

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
}