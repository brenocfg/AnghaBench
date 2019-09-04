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
struct i915_gpu_state {int ngtier; void* pgtbl_er; void* eir; void* ier; void** gtier; void* gac_eco; void* gam_ecochk; void* ccid; void* done_reg; void* error; void* derrmr; void* forcewake; void* gfx_mode; void* gab_ctl; void* fault_data1; void* fault_data0; void* err_int; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCID ; 
 int /*<<< orphan*/  DEIER ; 
 int /*<<< orphan*/  DERRMR ; 
 int /*<<< orphan*/  DONE_REG ; 
 int /*<<< orphan*/  EIR ; 
 int /*<<< orphan*/  ERROR_GEN6 ; 
 int /*<<< orphan*/  FORCEWAKE ; 
 int /*<<< orphan*/  FORCEWAKE_MT ; 
 int /*<<< orphan*/  FORCEWAKE_VLV ; 
 int /*<<< orphan*/  GAB_CTL ; 
 int /*<<< orphan*/  GAC_ECO_BITS ; 
 int /*<<< orphan*/  GAM_ECOCHK ; 
 int /*<<< orphan*/  GEN11_CRYPTO_RSVD_INTR_ENABLE ; 
 int /*<<< orphan*/  GEN11_GPM_WGBOXPERF_INTR_ENABLE ; 
 int /*<<< orphan*/  GEN11_GUC_SG_INTR_ENABLE ; 
 int /*<<< orphan*/  GEN11_GUNIT_CSME_INTR_ENABLE ; 
 int /*<<< orphan*/  GEN11_RENDER_COPY_INTR_ENABLE ; 
 int /*<<< orphan*/  GEN11_VCS_VECS_INTR_ENABLE ; 
 int /*<<< orphan*/  GEN7_ERR_INT ; 
 int /*<<< orphan*/  GEN8_DE_MISC_IER ; 
 int /*<<< orphan*/  GEN8_FAULT_TLB_DATA0 ; 
 int /*<<< orphan*/  GEN8_FAULT_TLB_DATA1 ; 
 int /*<<< orphan*/  GEN8_GT_IER (int) ; 
 int /*<<< orphan*/  GFX_MODE ; 
 int /*<<< orphan*/  GTIER ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_i915_private*) ; 
 void* I915_READ (int /*<<< orphan*/ ) ; 
 void* I915_READ16 (int /*<<< orphan*/ ) ; 
 void* I915_READ_FW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IER ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN2 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN6 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN7 (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PGTBL_ER ; 
 int /*<<< orphan*/  VLV_IER ; 

__attribute__((used)) static void capture_reg_state(struct i915_gpu_state *error)
{
	struct drm_i915_private *dev_priv = error->i915;
	int i;

	/* General organization
	 * 1. Registers specific to a single generation
	 * 2. Registers which belong to multiple generations
	 * 3. Feature specific registers.
	 * 4. Everything else
	 * Please try to follow the order.
	 */

	/* 1: Registers specific to a single generation */
	if (IS_VALLEYVIEW(dev_priv)) {
		error->gtier[0] = I915_READ(GTIER);
		error->ier = I915_READ(VLV_IER);
		error->forcewake = I915_READ_FW(FORCEWAKE_VLV);
	}

	if (IS_GEN7(dev_priv))
		error->err_int = I915_READ(GEN7_ERR_INT);

	if (INTEL_GEN(dev_priv) >= 8) {
		error->fault_data0 = I915_READ(GEN8_FAULT_TLB_DATA0);
		error->fault_data1 = I915_READ(GEN8_FAULT_TLB_DATA1);
	}

	if (IS_GEN6(dev_priv)) {
		error->forcewake = I915_READ_FW(FORCEWAKE);
		error->gab_ctl = I915_READ(GAB_CTL);
		error->gfx_mode = I915_READ(GFX_MODE);
	}

	/* 2: Registers which belong to multiple generations */
	if (INTEL_GEN(dev_priv) >= 7)
		error->forcewake = I915_READ_FW(FORCEWAKE_MT);

	if (INTEL_GEN(dev_priv) >= 6) {
		error->derrmr = I915_READ(DERRMR);
		error->error = I915_READ(ERROR_GEN6);
		error->done_reg = I915_READ(DONE_REG);
	}

	if (INTEL_GEN(dev_priv) >= 5)
		error->ccid = I915_READ(CCID);

	/* 3: Feature specific registers */
	if (IS_GEN6(dev_priv) || IS_GEN7(dev_priv)) {
		error->gam_ecochk = I915_READ(GAM_ECOCHK);
		error->gac_eco = I915_READ(GAC_ECO_BITS);
	}

	/* 4: Everything else */
	if (INTEL_GEN(dev_priv) >= 11) {
		error->ier = I915_READ(GEN8_DE_MISC_IER);
		error->gtier[0] = I915_READ(GEN11_RENDER_COPY_INTR_ENABLE);
		error->gtier[1] = I915_READ(GEN11_VCS_VECS_INTR_ENABLE);
		error->gtier[2] = I915_READ(GEN11_GUC_SG_INTR_ENABLE);
		error->gtier[3] = I915_READ(GEN11_GPM_WGBOXPERF_INTR_ENABLE);
		error->gtier[4] = I915_READ(GEN11_CRYPTO_RSVD_INTR_ENABLE);
		error->gtier[5] = I915_READ(GEN11_GUNIT_CSME_INTR_ENABLE);
		error->ngtier = 6;
	} else if (INTEL_GEN(dev_priv) >= 8) {
		error->ier = I915_READ(GEN8_DE_MISC_IER);
		for (i = 0; i < 4; i++)
			error->gtier[i] = I915_READ(GEN8_GT_IER(i));
		error->ngtier = 4;
	} else if (HAS_PCH_SPLIT(dev_priv)) {
		error->ier = I915_READ(DEIER);
		error->gtier[0] = I915_READ(GTIER);
		error->ngtier = 1;
	} else if (IS_GEN2(dev_priv)) {
		error->ier = I915_READ16(IER);
	} else if (!IS_VALLEYVIEW(dev_priv)) {
		error->ier = I915_READ(IER);
	}
	error->eir = I915_READ(EIR);
	error->pgtbl_er = I915_READ(PGTBL_ER);
}