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
typedef  int /*<<< orphan*/  u32 ;
struct sg_table {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct intel_uc_fw {int /*<<< orphan*/  rsa_offset; } ;
struct intel_guc {struct intel_uc_fw fw; } ;
struct i915_vma {struct sg_table* pages; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  rsa ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UOS_RSA_SCRATCH (int) ; 
 int UOS_RSA_SCRATCH_COUNT ; 
 struct drm_i915_private* guc_to_i915 (struct intel_guc*) ; 
 int sg_pcopy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int guc_xfer_rsa(struct intel_guc *guc, struct i915_vma *vma)
{
	struct drm_i915_private *dev_priv = guc_to_i915(guc);
	struct intel_uc_fw *guc_fw = &guc->fw;
	struct sg_table *sg = vma->pages;
	u32 rsa[UOS_RSA_SCRATCH_COUNT];
	int i;

	if (sg_pcopy_to_buffer(sg->sgl, sg->nents, rsa, sizeof(rsa),
			       guc_fw->rsa_offset) != sizeof(rsa))
		return -EINVAL;

	for (i = 0; i < UOS_RSA_SCRATCH_COUNT; i++)
		I915_WRITE(UOS_RSA_SCRATCH(i), rsa[i]);

	return 0;
}