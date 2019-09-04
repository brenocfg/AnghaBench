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
 int CGPSF_CLKGATE_DIS ; 
 int /*<<< orphan*/  GAMT_CHKN_BIT_REG ; 
 int GAMT_CHKN_DISABLE_L3_COH_PIPE ; 
 int GAMT_ECO_ENABLE_IN_PLACE_DECOMPRESS ; 
 int GAMW_ECO_DEV_CTX_RELOAD_DISABLE ; 
 int /*<<< orphan*/  GAMW_ECO_DEV_RW_IA_REG ; 
 int /*<<< orphan*/  GEN10_L3_CHICKEN_MODE_REGISTER ; 
 int /*<<< orphan*/  GEN10_SCRATCH_LNCF2 ; 
 int GEN11_ARBITRATION_PRIO_ORDER_MASK ; 
 int GEN11_BANK_HASH_ADDR_EXCL_BIT0 ; 
 int GEN11_BANK_HASH_ADDR_EXCL_MASK ; 
 int /*<<< orphan*/  GEN11_GACB_PERF_CTRL ; 
 int /*<<< orphan*/  GEN11_GLBLINVL ; 
 int GEN11_HASH_CTRL_BIT0 ; 
 int GEN11_HASH_CTRL_BIT4 ; 
 int GEN11_HASH_CTRL_EXCL_BIT0 ; 
 int GEN11_HASH_CTRL_EXCL_MASK ; 
 int GEN11_HASH_CTRL_MASK ; 
 int GEN11_I2M_WRITE_DISABLE ; 
 int GEN11_LQSC_CLEAN_EVICT_DISABLE ; 
 int /*<<< orphan*/  GEN11_LSN_UNSLCVC ; 
 int GEN11_LSN_UNSLCVC_GAFS_HALF_CL2_MAXALLOC ; 
 int GEN11_LSN_UNSLCVC_GAFS_HALF_SF_MAXALLOC ; 
 int /*<<< orphan*/  GEN8_GARBCNTL ; 
 int /*<<< orphan*/  GEN8_L3SQCREG4 ; 
 int GEN8_LQSC_FLUSH_COHERENT_LINES ; 
 int /*<<< orphan*/  GEN9_GAMT_ECO_REG_RW_IA ; 
 int GWUNIT_CLKGATE_DIS ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ICL_REVID_A0 ; 
 int /*<<< orphan*/  ICL_REVID_B0 ; 
 int /*<<< orphan*/  INF_UNIT_LEVEL_CLKGATE ; 
 scalar_t__ IS_ICL_REVID (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MSCUNIT_CLKGATE_DIS ; 
 int PMFLUSHDONE_LNEBLK ; 
 int PMFLUSHDONE_LNICRSDROP ; 
 int PMFLUSH_GAPL3UNBLOCK ; 
 int /*<<< orphan*/  SLICE_UNIT_LEVEL_CLKGATE ; 
 int /*<<< orphan*/  SUBSLICE_UNIT_LEVEL_CLKGATE ; 
 int /*<<< orphan*/  _3D_CHICKEN3 ; 
 int /*<<< orphan*/  _3D_CHICKEN3_AA_LINE_QUALITY_FIX_ENABLE ; 
 int _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wa_init_mcr (struct drm_i915_private*) ; 

__attribute__((used)) static void icl_gt_workarounds_apply(struct drm_i915_private *dev_priv)
{
	wa_init_mcr(dev_priv);

	/* This is not an Wa. Enable for better image quality */
	I915_WRITE(_3D_CHICKEN3,
		   _MASKED_BIT_ENABLE(_3D_CHICKEN3_AA_LINE_QUALITY_FIX_ENABLE));

	/* WaInPlaceDecompressionHang:icl */
	I915_WRITE(GEN9_GAMT_ECO_REG_RW_IA, I915_READ(GEN9_GAMT_ECO_REG_RW_IA) |
					    GAMT_ECO_ENABLE_IN_PLACE_DECOMPRESS);

	/* WaPipelineFlushCoherentLines:icl */
	I915_WRITE(GEN8_L3SQCREG4, I915_READ(GEN8_L3SQCREG4) |
				   GEN8_LQSC_FLUSH_COHERENT_LINES);

	/* Wa_1405543622:icl
	 * Formerly known as WaGAPZPriorityScheme
	 */
	I915_WRITE(GEN8_GARBCNTL, I915_READ(GEN8_GARBCNTL) |
				  GEN11_ARBITRATION_PRIO_ORDER_MASK);

	/* Wa_1604223664:icl
	 * Formerly known as WaL3BankAddressHashing
	 */
	I915_WRITE(GEN8_GARBCNTL,
		   (I915_READ(GEN8_GARBCNTL) & ~GEN11_HASH_CTRL_EXCL_MASK) |
		   GEN11_HASH_CTRL_EXCL_BIT0);
	I915_WRITE(GEN11_GLBLINVL,
		   (I915_READ(GEN11_GLBLINVL) & ~GEN11_BANK_HASH_ADDR_EXCL_MASK) |
		   GEN11_BANK_HASH_ADDR_EXCL_BIT0);

	/* WaModifyGamTlbPartitioning:icl */
	I915_WRITE(GEN11_GACB_PERF_CTRL,
		   (I915_READ(GEN11_GACB_PERF_CTRL) & ~GEN11_HASH_CTRL_MASK) |
		   GEN11_HASH_CTRL_BIT0 | GEN11_HASH_CTRL_BIT4);

	/* Wa_1405733216:icl
	 * Formerly known as WaDisableCleanEvicts
	 */
	I915_WRITE(GEN8_L3SQCREG4, I915_READ(GEN8_L3SQCREG4) |
				   GEN11_LQSC_CLEAN_EVICT_DISABLE);

	/* Wa_1405766107:icl
	 * Formerly known as WaCL2SFHalfMaxAlloc
	 */
	I915_WRITE(GEN11_LSN_UNSLCVC, I915_READ(GEN11_LSN_UNSLCVC) |
				      GEN11_LSN_UNSLCVC_GAFS_HALF_SF_MAXALLOC |
				      GEN11_LSN_UNSLCVC_GAFS_HALF_CL2_MAXALLOC);

	/* Wa_220166154:icl
	 * Formerly known as WaDisCtxReload
	 */
	I915_WRITE(GAMW_ECO_DEV_RW_IA_REG, I915_READ(GAMW_ECO_DEV_RW_IA_REG) |
					   GAMW_ECO_DEV_CTX_RELOAD_DISABLE);

	/* Wa_1405779004:icl (pre-prod) */
	if (IS_ICL_REVID(dev_priv, ICL_REVID_A0, ICL_REVID_A0))
		I915_WRITE(SLICE_UNIT_LEVEL_CLKGATE,
			   I915_READ(SLICE_UNIT_LEVEL_CLKGATE) |
			   MSCUNIT_CLKGATE_DIS);

	/* Wa_1406680159:icl */
	I915_WRITE(SUBSLICE_UNIT_LEVEL_CLKGATE,
		   I915_READ(SUBSLICE_UNIT_LEVEL_CLKGATE) |
		   GWUNIT_CLKGATE_DIS);

	/* Wa_1604302699:icl */
	I915_WRITE(GEN10_L3_CHICKEN_MODE_REGISTER,
		   I915_READ(GEN10_L3_CHICKEN_MODE_REGISTER) |
		   GEN11_I2M_WRITE_DISABLE);

	/* Wa_1406838659:icl (pre-prod) */
	if (IS_ICL_REVID(dev_priv, ICL_REVID_A0, ICL_REVID_B0))
		I915_WRITE(INF_UNIT_LEVEL_CLKGATE,
			   I915_READ(INF_UNIT_LEVEL_CLKGATE) |
			   CGPSF_CLKGATE_DIS);

	/* WaForwardProgressSoftReset:icl */
	I915_WRITE(GEN10_SCRATCH_LNCF2,
		   I915_READ(GEN10_SCRATCH_LNCF2) |
		   PMFLUSHDONE_LNICRSDROP |
		   PMFLUSH_GAPL3UNBLOCK |
		   PMFLUSHDONE_LNEBLK);

	/* Wa_1406463099:icl
	 * Formerly known as WaGamTlbPendError
	 */
	I915_WRITE(GAMT_CHKN_BIT_REG,
		   I915_READ(GAMT_CHKN_BIT_REG) |
		   GAMT_CHKN_DISABLE_L3_COH_PIPE);
}