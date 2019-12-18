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
typedef  int /*<<< orphan*/  u16 ;
struct drm_i915_private {int dummy; } ;
struct dram_dimm_info {int /*<<< orphan*/  ranks; int /*<<< orphan*/  width; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  cnl_get_dimm_ranks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnl_get_dimm_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnl_get_dimm_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_get_dimm_ranks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_get_dimm_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_get_dimm_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_is_16gb_dimm (struct dram_dimm_info*) ; 
 int /*<<< orphan*/  yesno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
skl_dram_get_dimm_info(struct drm_i915_private *dev_priv,
		       struct dram_dimm_info *dimm,
		       int channel, char dimm_name, u16 val)
{
	if (INTEL_GEN(dev_priv) >= 10) {
		dimm->size = cnl_get_dimm_size(val);
		dimm->width = cnl_get_dimm_width(val);
		dimm->ranks = cnl_get_dimm_ranks(val);
	} else {
		dimm->size = skl_get_dimm_size(val);
		dimm->width = skl_get_dimm_width(val);
		dimm->ranks = skl_get_dimm_ranks(val);
	}

	DRM_DEBUG_KMS("CH%u DIMM %c size: %u GB, width: X%u, ranks: %u, 16Gb DIMMs: %s\n",
		      channel, dimm_name, dimm->size, dimm->width, dimm->ranks,
		      yesno(skl_is_16gb_dimm(dimm)));
}