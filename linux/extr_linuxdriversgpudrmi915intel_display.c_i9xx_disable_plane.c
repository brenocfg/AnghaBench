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
struct intel_plane {int i9xx_plane; TYPE_1__ base; } ;
struct intel_crtc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_2__ uncore; } ;
typedef  enum i9xx_plane_id { ____Placeholder_i9xx_plane_id } i9xx_plane_id ;

/* Variables and functions */
 int /*<<< orphan*/  DSPADDR (int) ; 
 int /*<<< orphan*/  DSPCNTR (int) ; 
 int /*<<< orphan*/  DSPSURF (int) ; 
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  POSTING_READ_FW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i9xx_disable_plane(struct intel_plane *plane,
			       struct intel_crtc *crtc)
{
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);
	enum i9xx_plane_id i9xx_plane = plane->i9xx_plane;
	unsigned long irqflags;

	spin_lock_irqsave(&dev_priv->uncore.lock, irqflags);

	I915_WRITE_FW(DSPCNTR(i9xx_plane), 0);
	if (INTEL_GEN(dev_priv) >= 4)
		I915_WRITE_FW(DSPSURF(i9xx_plane), 0);
	else
		I915_WRITE_FW(DSPADDR(i9xx_plane), 0);
	POSTING_READ_FW(DSPCNTR(i9xx_plane));

	spin_unlock_irqrestore(&dev_priv->uncore.lock, irqflags);
}