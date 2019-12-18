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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_GFX_FMIN_AT_VMIN_FUSE ; 
 int FB_GFX_FMIN_AT_VMIN_FUSE_SHIFT ; 
 int FB_GFX_FREQ_FUSE_MASK ; 
 int vlv_punit_read (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 cherryview_rps_min_freq(struct drm_i915_private *dev_priv)
{
	u32 val, rpn;

	val = vlv_punit_read(dev_priv, FB_GFX_FMIN_AT_VMIN_FUSE);
	rpn = ((val >> FB_GFX_FMIN_AT_VMIN_FUSE_SHIFT) &
		       FB_GFX_FREQ_FUSE_MASK);

	return rpn;
}