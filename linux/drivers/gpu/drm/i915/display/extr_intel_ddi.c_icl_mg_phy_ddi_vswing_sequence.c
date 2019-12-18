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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int port; TYPE_1__ base; } ;
struct icl_mg_phy_ddi_buf_trans {int /*<<< orphan*/  cri_txdeemph_override_11_6; int /*<<< orphan*/  cri_txdeemph_override_5_0; int /*<<< orphan*/  cri_txdeemph_override_17_12; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int ARRAY_SIZE (struct icl_mg_phy_ddi_buf_trans*) ; 
 int CFG_AMI_CK_DIV_OVERRIDE_EN ; 
 int CFG_AMI_CK_DIV_OVERRIDE_VAL (int) ; 
 int CFG_AMI_CK_DIV_OVERRIDE_VAL_MASK ; 
 int CFG_LOW_RATE_LKREN_EN ; 
 int CRI_CALCINIT ; 
 int CRI_TXDEEMPH_OVERRIDE_11_6 (int /*<<< orphan*/ ) ; 
 int CRI_TXDEEMPH_OVERRIDE_11_6_MASK ; 
 int CRI_TXDEEMPH_OVERRIDE_17_12 (int /*<<< orphan*/ ) ; 
 int CRI_TXDEEMPH_OVERRIDE_17_12_MASK ; 
 int CRI_TXDEEMPH_OVERRIDE_5_0 (int /*<<< orphan*/ ) ; 
 int CRI_TXDEEMPH_OVERRIDE_5_0_MASK ; 
 int CRI_TXDEEMPH_OVERRIDE_EN ; 
 int CRI_USE_FS32 ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MG_CLKHUB (int,int) ; 
 int /*<<< orphan*/  MG_TX1_DCC (int,int) ; 
 int /*<<< orphan*/  MG_TX1_DRVCTRL (int,int) ; 
 int /*<<< orphan*/  MG_TX1_LINK_PARAMS (int,int) ; 
 int /*<<< orphan*/  MG_TX1_PISO_READLOAD (int,int) ; 
 int /*<<< orphan*/  MG_TX1_SWINGCTRL (int,int) ; 
 int /*<<< orphan*/  MG_TX2_DCC (int,int) ; 
 int /*<<< orphan*/  MG_TX2_DRVCTRL (int,int) ; 
 int /*<<< orphan*/  MG_TX2_LINK_PARAMS (int,int) ; 
 int /*<<< orphan*/  MG_TX2_PISO_READLOAD (int,int) ; 
 int /*<<< orphan*/  MG_TX2_SWINGCTRL (int,int) ; 
 struct icl_mg_phy_ddi_buf_trans* icl_mg_phy_ddi_translations ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void icl_mg_phy_ddi_vswing_sequence(struct intel_encoder *encoder,
					   int link_clock,
					   u32 level)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	enum port port = encoder->port;
	const struct icl_mg_phy_ddi_buf_trans *ddi_translations;
	u32 n_entries, val;
	int ln;

	n_entries = ARRAY_SIZE(icl_mg_phy_ddi_translations);
	ddi_translations = icl_mg_phy_ddi_translations;
	/* The table does not have values for level 3 and level 9. */
	if (level >= n_entries || level == 3 || level == 9) {
		DRM_DEBUG_KMS("DDI translation not found for level %d. Using %d instead.",
			      level, n_entries - 2);
		level = n_entries - 2;
	}

	/* Set MG_TX_LINK_PARAMS cri_use_fs32 to 0. */
	for (ln = 0; ln < 2; ln++) {
		val = I915_READ(MG_TX1_LINK_PARAMS(ln, port));
		val &= ~CRI_USE_FS32;
		I915_WRITE(MG_TX1_LINK_PARAMS(ln, port), val);

		val = I915_READ(MG_TX2_LINK_PARAMS(ln, port));
		val &= ~CRI_USE_FS32;
		I915_WRITE(MG_TX2_LINK_PARAMS(ln, port), val);
	}

	/* Program MG_TX_SWINGCTRL with values from vswing table */
	for (ln = 0; ln < 2; ln++) {
		val = I915_READ(MG_TX1_SWINGCTRL(ln, port));
		val &= ~CRI_TXDEEMPH_OVERRIDE_17_12_MASK;
		val |= CRI_TXDEEMPH_OVERRIDE_17_12(
			ddi_translations[level].cri_txdeemph_override_17_12);
		I915_WRITE(MG_TX1_SWINGCTRL(ln, port), val);

		val = I915_READ(MG_TX2_SWINGCTRL(ln, port));
		val &= ~CRI_TXDEEMPH_OVERRIDE_17_12_MASK;
		val |= CRI_TXDEEMPH_OVERRIDE_17_12(
			ddi_translations[level].cri_txdeemph_override_17_12);
		I915_WRITE(MG_TX2_SWINGCTRL(ln, port), val);
	}

	/* Program MG_TX_DRVCTRL with values from vswing table */
	for (ln = 0; ln < 2; ln++) {
		val = I915_READ(MG_TX1_DRVCTRL(ln, port));
		val &= ~(CRI_TXDEEMPH_OVERRIDE_11_6_MASK |
			 CRI_TXDEEMPH_OVERRIDE_5_0_MASK);
		val |= CRI_TXDEEMPH_OVERRIDE_5_0(
			ddi_translations[level].cri_txdeemph_override_5_0) |
			CRI_TXDEEMPH_OVERRIDE_11_6(
				ddi_translations[level].cri_txdeemph_override_11_6) |
			CRI_TXDEEMPH_OVERRIDE_EN;
		I915_WRITE(MG_TX1_DRVCTRL(ln, port), val);

		val = I915_READ(MG_TX2_DRVCTRL(ln, port));
		val &= ~(CRI_TXDEEMPH_OVERRIDE_11_6_MASK |
			 CRI_TXDEEMPH_OVERRIDE_5_0_MASK);
		val |= CRI_TXDEEMPH_OVERRIDE_5_0(
			ddi_translations[level].cri_txdeemph_override_5_0) |
			CRI_TXDEEMPH_OVERRIDE_11_6(
				ddi_translations[level].cri_txdeemph_override_11_6) |
			CRI_TXDEEMPH_OVERRIDE_EN;
		I915_WRITE(MG_TX2_DRVCTRL(ln, port), val);

		/* FIXME: Program CRI_LOADGEN_SEL after the spec is updated */
	}

	/*
	 * Program MG_CLKHUB<LN, port being used> with value from frequency table
	 * In case of Legacy mode on MG PHY, both TX1 and TX2 enabled so use the
	 * values from table for which TX1 and TX2 enabled.
	 */
	for (ln = 0; ln < 2; ln++) {
		val = I915_READ(MG_CLKHUB(ln, port));
		if (link_clock < 300000)
			val |= CFG_LOW_RATE_LKREN_EN;
		else
			val &= ~CFG_LOW_RATE_LKREN_EN;
		I915_WRITE(MG_CLKHUB(ln, port), val);
	}

	/* Program the MG_TX_DCC<LN, port being used> based on the link frequency */
	for (ln = 0; ln < 2; ln++) {
		val = I915_READ(MG_TX1_DCC(ln, port));
		val &= ~CFG_AMI_CK_DIV_OVERRIDE_VAL_MASK;
		if (link_clock <= 500000) {
			val &= ~CFG_AMI_CK_DIV_OVERRIDE_EN;
		} else {
			val |= CFG_AMI_CK_DIV_OVERRIDE_EN |
				CFG_AMI_CK_DIV_OVERRIDE_VAL(1);
		}
		I915_WRITE(MG_TX1_DCC(ln, port), val);

		val = I915_READ(MG_TX2_DCC(ln, port));
		val &= ~CFG_AMI_CK_DIV_OVERRIDE_VAL_MASK;
		if (link_clock <= 500000) {
			val &= ~CFG_AMI_CK_DIV_OVERRIDE_EN;
		} else {
			val |= CFG_AMI_CK_DIV_OVERRIDE_EN |
				CFG_AMI_CK_DIV_OVERRIDE_VAL(1);
		}
		I915_WRITE(MG_TX2_DCC(ln, port), val);
	}

	/* Program MG_TX_PISO_READLOAD with values from vswing table */
	for (ln = 0; ln < 2; ln++) {
		val = I915_READ(MG_TX1_PISO_READLOAD(ln, port));
		val |= CRI_CALCINIT;
		I915_WRITE(MG_TX1_PISO_READLOAD(ln, port), val);

		val = I915_READ(MG_TX2_PISO_READLOAD(ln, port));
		val |= CRI_CALCINIT;
		I915_WRITE(MG_TX2_PISO_READLOAD(ln, port), val);
	}
}