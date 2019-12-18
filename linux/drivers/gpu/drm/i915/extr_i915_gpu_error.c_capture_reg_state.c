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
struct intel_uncore {int dummy; } ;
struct i915_gpu_state {int ngtier; void* pgtbl_er; void* eir; void* ier; void** gtier; void* gac_eco; void* gam_ecochk; void* ccid; void* done_reg; void* error; void* derrmr; void* forcewake; void* gfx_mode; void* gab_ctl; void* fault_data1; void* fault_data0; void* err_int; struct drm_i915_private* i915; } ;
struct drm_i915_private {struct intel_uncore uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCID (int /*<<< orphan*/ ) ; 
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
 int /*<<< orphan*/  GEN12_FAULT_TLB_DATA0 ; 
 int /*<<< orphan*/  GEN12_FAULT_TLB_DATA1 ; 
 int /*<<< orphan*/  GEN2_IER ; 
 int /*<<< orphan*/  GEN7_ERR_INT ; 
 int /*<<< orphan*/  GEN8_DE_MISC_IER ; 
 int /*<<< orphan*/  GEN8_FAULT_TLB_DATA0 ; 
 int /*<<< orphan*/  GEN8_FAULT_TLB_DATA1 ; 
 int /*<<< orphan*/  GEN8_GT_IER (int) ; 
 int /*<<< orphan*/  GFX_MODE ; 
 int /*<<< orphan*/  GTIER ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_GEN_RANGE (struct drm_i915_private*,int,int) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PGTBL_ER ; 
 int /*<<< orphan*/  RENDER_RING_BASE ; 
 int /*<<< orphan*/  VLV_IER ; 
 void* intel_uncore_read (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 void* intel_uncore_read16 (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 void* intel_uncore_read_fw (struct intel_uncore*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void capture_reg_state(struct i915_gpu_state *error)
{
	struct drm_i915_private *i915 = error->i915;
	struct intel_uncore *uncore = &i915->uncore;
	int i;

	/* General organization
	 * 1. Registers specific to a single generation
	 * 2. Registers which belong to multiple generations
	 * 3. Feature specific registers.
	 * 4. Everything else
	 * Please try to follow the order.
	 */

	/* 1: Registers specific to a single generation */
	if (IS_VALLEYVIEW(i915)) {
		error->gtier[0] = intel_uncore_read(uncore, GTIER);
		error->ier = intel_uncore_read(uncore, VLV_IER);
		error->forcewake = intel_uncore_read_fw(uncore, FORCEWAKE_VLV);
	}

	if (IS_GEN(i915, 7))
		error->err_int = intel_uncore_read(uncore, GEN7_ERR_INT);

	if (INTEL_GEN(i915) >= 12) {
		error->fault_data0 = intel_uncore_read(uncore,
						       GEN12_FAULT_TLB_DATA0);
		error->fault_data1 = intel_uncore_read(uncore,
						       GEN12_FAULT_TLB_DATA1);
	} else if (INTEL_GEN(i915) >= 8) {
		error->fault_data0 = intel_uncore_read(uncore,
						       GEN8_FAULT_TLB_DATA0);
		error->fault_data1 = intel_uncore_read(uncore,
						       GEN8_FAULT_TLB_DATA1);
	}

	if (IS_GEN(i915, 6)) {
		error->forcewake = intel_uncore_read_fw(uncore, FORCEWAKE);
		error->gab_ctl = intel_uncore_read(uncore, GAB_CTL);
		error->gfx_mode = intel_uncore_read(uncore, GFX_MODE);
	}

	/* 2: Registers which belong to multiple generations */
	if (INTEL_GEN(i915) >= 7)
		error->forcewake = intel_uncore_read_fw(uncore, FORCEWAKE_MT);

	if (INTEL_GEN(i915) >= 6) {
		error->derrmr = intel_uncore_read(uncore, DERRMR);
		if (INTEL_GEN(i915) < 12) {
			error->error = intel_uncore_read(uncore, ERROR_GEN6);
			error->done_reg = intel_uncore_read(uncore, DONE_REG);
		}
	}

	if (INTEL_GEN(i915) >= 5)
		error->ccid = intel_uncore_read(uncore, CCID(RENDER_RING_BASE));

	/* 3: Feature specific registers */
	if (IS_GEN_RANGE(i915, 6, 7)) {
		error->gam_ecochk = intel_uncore_read(uncore, GAM_ECOCHK);
		error->gac_eco = intel_uncore_read(uncore, GAC_ECO_BITS);
	}

	/* 4: Everything else */
	if (INTEL_GEN(i915) >= 11) {
		error->ier = intel_uncore_read(uncore, GEN8_DE_MISC_IER);
		error->gtier[0] =
			intel_uncore_read(uncore,
					  GEN11_RENDER_COPY_INTR_ENABLE);
		error->gtier[1] =
			intel_uncore_read(uncore, GEN11_VCS_VECS_INTR_ENABLE);
		error->gtier[2] =
			intel_uncore_read(uncore, GEN11_GUC_SG_INTR_ENABLE);
		error->gtier[3] =
			intel_uncore_read(uncore,
					  GEN11_GPM_WGBOXPERF_INTR_ENABLE);
		error->gtier[4] =
			intel_uncore_read(uncore,
					  GEN11_CRYPTO_RSVD_INTR_ENABLE);
		error->gtier[5] =
			intel_uncore_read(uncore,
					  GEN11_GUNIT_CSME_INTR_ENABLE);
		error->ngtier = 6;
	} else if (INTEL_GEN(i915) >= 8) {
		error->ier = intel_uncore_read(uncore, GEN8_DE_MISC_IER);
		for (i = 0; i < 4; i++)
			error->gtier[i] = intel_uncore_read(uncore,
							    GEN8_GT_IER(i));
		error->ngtier = 4;
	} else if (HAS_PCH_SPLIT(i915)) {
		error->ier = intel_uncore_read(uncore, DEIER);
		error->gtier[0] = intel_uncore_read(uncore, GTIER);
		error->ngtier = 1;
	} else if (IS_GEN(i915, 2)) {
		error->ier = intel_uncore_read16(uncore, GEN2_IER);
	} else if (!IS_VALLEYVIEW(i915)) {
		error->ier = intel_uncore_read(uncore, GEN2_IER);
	}
	error->eir = intel_uncore_read(uncore, EIR);
	error->pgtbl_er = intel_uncore_read(uncore, PGTBL_ER);
}