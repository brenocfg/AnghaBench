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
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 int /*<<< orphan*/  bdw_setup_private_ppat (struct drm_i915_private*) ; 
 int /*<<< orphan*/  chv_setup_private_ppat (struct drm_i915_private*) ; 
 int /*<<< orphan*/  cnl_setup_private_ppat (struct drm_i915_private*) ; 
 int /*<<< orphan*/  tgl_setup_private_ppat (struct drm_i915_private*) ; 

__attribute__((used)) static void setup_private_pat(struct drm_i915_private *dev_priv)
{
	GEM_BUG_ON(INTEL_GEN(dev_priv) < 8);

	if (INTEL_GEN(dev_priv) >= 12)
		tgl_setup_private_ppat(dev_priv);
	else if (INTEL_GEN(dev_priv) >= 10)
		cnl_setup_private_ppat(dev_priv);
	else if (IS_CHERRYVIEW(dev_priv) || IS_GEN9_LP(dev_priv))
		chv_setup_private_ppat(dev_priv);
	else
		bdw_setup_private_ppat(dev_priv);
}