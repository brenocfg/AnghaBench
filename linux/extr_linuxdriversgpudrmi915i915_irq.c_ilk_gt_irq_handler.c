#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct drm_i915_private {int /*<<< orphan*/ * engine; } ;

/* Variables and functions */
 int GT_RENDER_USER_INTERRUPT ; 
 int ILK_BSD_USER_INTERRUPT ; 
 size_t RCS ; 
 size_t VCS ; 
 int /*<<< orphan*/  notify_ring (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ilk_gt_irq_handler(struct drm_i915_private *dev_priv,
			       u32 gt_iir)
{
	if (gt_iir & GT_RENDER_USER_INTERRUPT)
		notify_ring(dev_priv->engine[RCS]);
	if (gt_iir & ILK_BSD_USER_INTERRUPT)
		notify_ring(dev_priv->engine[VCS]);
}