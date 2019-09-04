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
 scalar_t__ IS_GEN2 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN3 (struct drm_i915_private*) ; 
 scalar_t__ IS_I830 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PRB1_BASE ; 
 int /*<<< orphan*/  PRB2_BASE ; 
 int /*<<< orphan*/  SRB0_BASE ; 
 int /*<<< orphan*/  SRB1_BASE ; 
 int /*<<< orphan*/  SRB2_BASE ; 
 int /*<<< orphan*/  SRB3_BASE ; 
 int /*<<< orphan*/  init_unused_ring (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_unused_rings(struct drm_i915_private *dev_priv)
{
	if (IS_I830(dev_priv)) {
		init_unused_ring(dev_priv, PRB1_BASE);
		init_unused_ring(dev_priv, SRB0_BASE);
		init_unused_ring(dev_priv, SRB1_BASE);
		init_unused_ring(dev_priv, SRB2_BASE);
		init_unused_ring(dev_priv, SRB3_BASE);
	} else if (IS_GEN2(dev_priv)) {
		init_unused_ring(dev_priv, SRB0_BASE);
		init_unused_ring(dev_priv, SRB1_BASE);
	} else if (IS_GEN3(dev_priv)) {
		init_unused_ring(dev_priv, PRB1_BASE);
		init_unused_ring(dev_priv, PRB2_BASE);
	}
}