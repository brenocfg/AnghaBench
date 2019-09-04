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
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {int id; int pipe; TYPE_1__ base; } ;
struct intel_crtc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_2__ uncore; } ;
typedef  enum plane_id { ____Placeholder_plane_id } plane_id ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLANE_CTL (int,int) ; 
 int /*<<< orphan*/  PLANE_SURF (int,int) ; 
 int /*<<< orphan*/  POSTING_READ_FW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

void
skl_disable_plane(struct intel_plane *plane, struct intel_crtc *crtc)
{
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);
	enum plane_id plane_id = plane->id;
	enum pipe pipe = plane->pipe;
	unsigned long irqflags;

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	I915_WRITE_FW(PLANE_CTL(pipe, plane_id), 0);

	I915_WRITE_FW(PLANE_SURF(pipe, plane_id), 0);
	POSTING_READ_FW(PLANE_SURF(pipe, plane_id));

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
}