#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int fw_domains; } ;
struct drm_i915_private {TYPE_1__ uncore; } ;
typedef  enum forcewake_domains { ____Placeholder_forcewake_domains } forcewake_domains ;
typedef  enum forcewake_domain_id { ____Placeholder_forcewake_domain_id } forcewake_domain_id ;

/* Variables and functions */
 int BIT (int) ; 
 int FW_DOMAIN_ID_MEDIA_VDBOX0 ; 
 int FW_DOMAIN_ID_MEDIA_VEBOX0 ; 
 scalar_t__ HAS_ENGINE (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int I915_MAX_VCS ; 
 int I915_MAX_VECS ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  _VCS (int) ; 
 int /*<<< orphan*/  _VECS (int) ; 
 int /*<<< orphan*/  fw_domain_fini (struct drm_i915_private*,int) ; 

void intel_uncore_prune(struct drm_i915_private *dev_priv)
{
	if (INTEL_GEN(dev_priv) >= 11) {
		enum forcewake_domains fw_domains = dev_priv->uncore.fw_domains;
		enum forcewake_domain_id domain_id;
		int i;

		for (i = 0; i < I915_MAX_VCS; i++) {
			domain_id = FW_DOMAIN_ID_MEDIA_VDBOX0 + i;

			if (HAS_ENGINE(dev_priv, _VCS(i)))
				continue;

			if (fw_domains & BIT(domain_id))
				fw_domain_fini(dev_priv, domain_id);
		}

		for (i = 0; i < I915_MAX_VECS; i++) {
			domain_id = FW_DOMAIN_ID_MEDIA_VEBOX0 + i;

			if (HAS_ENGINE(dev_priv, _VECS(i)))
				continue;

			if (fw_domains & BIT(domain_id))
				fw_domain_fini(dev_priv, domain_id);
		}
	}
}