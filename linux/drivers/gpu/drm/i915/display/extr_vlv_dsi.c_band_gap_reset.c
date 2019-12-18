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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  vlv_flisdsi_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vlv_flisdsi_put (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vlv_flisdsi_write (struct drm_i915_private*,int,int) ; 

__attribute__((used)) static void band_gap_reset(struct drm_i915_private *dev_priv)
{
	vlv_flisdsi_get(dev_priv);

	vlv_flisdsi_write(dev_priv, 0x08, 0x0001);
	vlv_flisdsi_write(dev_priv, 0x0F, 0x0005);
	vlv_flisdsi_write(dev_priv, 0x0F, 0x0025);
	udelay(150);
	vlv_flisdsi_write(dev_priv, 0x0F, 0x0000);
	vlv_flisdsi_write(dev_priv, 0x08, 0x0000);

	vlv_flisdsi_put(dev_priv);
}