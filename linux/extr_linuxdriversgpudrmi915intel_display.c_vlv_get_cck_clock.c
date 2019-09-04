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
struct drm_i915_private {int /*<<< orphan*/  sb_lock; } ;

/* Variables and functions */
 int CCK_FREQUENCY_STATUS ; 
 int CCK_FREQUENCY_STATUS_SHIFT ; 
 int CCK_FREQUENCY_VALUES ; 
 int DIV_ROUND_CLOSEST (int,int) ; 
 int /*<<< orphan*/  WARN (int,char*,char const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vlv_cck_read (struct drm_i915_private*,int) ; 

int vlv_get_cck_clock(struct drm_i915_private *dev_priv,
		      const char *name, u32 reg, int ref_freq)
{
	u32 val;
	int divider;

	mutex_lock(&dev_priv->sb_lock);
	val = vlv_cck_read(dev_priv, reg);
	mutex_unlock(&dev_priv->sb_lock);

	divider = val & CCK_FREQUENCY_VALUES;

	WARN((val & CCK_FREQUENCY_STATUS) !=
	     (divider << CCK_FREQUENCY_STATUS_SHIFT),
	     "%s change in progress\n", name);

	return DIV_ROUND_CLOSEST(ref_freq << 1, divider + 1);
}