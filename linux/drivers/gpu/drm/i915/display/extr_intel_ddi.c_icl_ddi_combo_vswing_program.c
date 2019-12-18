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
typedef  size_t u32 ;
struct drm_i915_private {int dummy; } ;
struct cnl_ddi_buf_trans {int /*<<< orphan*/  dw7_n_scalar; int /*<<< orphan*/  dw4_cursor_coeff; int /*<<< orphan*/  dw4_post_cursor_2; int /*<<< orphan*/  dw4_post_cursor_1; int /*<<< orphan*/  dw2_swing_sel; } ;
typedef  enum phy { ____Placeholder_phy } phy ;

/* Variables and functions */
 size_t CURSOR_COEFF (int /*<<< orphan*/ ) ; 
 size_t CURSOR_COEFF_MASK ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,size_t,size_t) ; 
 size_t I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ICL_PORT_TX_DW2_GRP (int) ; 
 int /*<<< orphan*/  ICL_PORT_TX_DW2_LN0 (int) ; 
 int /*<<< orphan*/  ICL_PORT_TX_DW4_LN (int,int) ; 
 int /*<<< orphan*/  ICL_PORT_TX_DW5_GRP (int) ; 
 int /*<<< orphan*/  ICL_PORT_TX_DW5_LN0 (int) ; 
 int /*<<< orphan*/  ICL_PORT_TX_DW7_GRP (int) ; 
 int /*<<< orphan*/  ICL_PORT_TX_DW7_LN0 (int) ; 
 size_t N_SCALAR (int /*<<< orphan*/ ) ; 
 size_t N_SCALAR_MASK ; 
 size_t POST_CURSOR_1 (int /*<<< orphan*/ ) ; 
 size_t POST_CURSOR_1_MASK ; 
 size_t POST_CURSOR_2 (int /*<<< orphan*/ ) ; 
 size_t POST_CURSOR_2_MASK ; 
 size_t RCOMP_SCALAR (int) ; 
 size_t RCOMP_SCALAR_MASK ; 
 size_t RTERM_SELECT (int) ; 
 size_t RTERM_SELECT_MASK ; 
 size_t SCALING_MODE_SEL (int) ; 
 size_t SCALING_MODE_SEL_MASK ; 
 size_t SWING_SEL_LOWER (int /*<<< orphan*/ ) ; 
 size_t SWING_SEL_LOWER_MASK ; 
 size_t SWING_SEL_UPPER (int /*<<< orphan*/ ) ; 
 size_t SWING_SEL_UPPER_MASK ; 
 size_t TAP2_DISABLE ; 
 size_t TAP3_DISABLE ; 
 struct cnl_ddi_buf_trans* icl_get_combo_buf_trans (struct drm_i915_private*,int,int,size_t*) ; 

__attribute__((used)) static void icl_ddi_combo_vswing_program(struct drm_i915_private *dev_priv,
					u32 level, enum phy phy, int type,
					int rate)
{
	const struct cnl_ddi_buf_trans *ddi_translations = NULL;
	u32 n_entries, val;
	int ln;

	ddi_translations = icl_get_combo_buf_trans(dev_priv, type, rate,
						   &n_entries);
	if (!ddi_translations)
		return;

	if (level >= n_entries) {
		DRM_DEBUG_KMS("DDI translation not found for level %d. Using %d instead.", level, n_entries - 1);
		level = n_entries - 1;
	}

	/* Set PORT_TX_DW5 */
	val = I915_READ(ICL_PORT_TX_DW5_LN0(phy));
	val &= ~(SCALING_MODE_SEL_MASK | RTERM_SELECT_MASK |
		  TAP2_DISABLE | TAP3_DISABLE);
	val |= SCALING_MODE_SEL(0x2);
	val |= RTERM_SELECT(0x6);
	val |= TAP3_DISABLE;
	I915_WRITE(ICL_PORT_TX_DW5_GRP(phy), val);

	/* Program PORT_TX_DW2 */
	val = I915_READ(ICL_PORT_TX_DW2_LN0(phy));
	val &= ~(SWING_SEL_LOWER_MASK | SWING_SEL_UPPER_MASK |
		 RCOMP_SCALAR_MASK);
	val |= SWING_SEL_UPPER(ddi_translations[level].dw2_swing_sel);
	val |= SWING_SEL_LOWER(ddi_translations[level].dw2_swing_sel);
	/* Program Rcomp scalar for every table entry */
	val |= RCOMP_SCALAR(0x98);
	I915_WRITE(ICL_PORT_TX_DW2_GRP(phy), val);

	/* Program PORT_TX_DW4 */
	/* We cannot write to GRP. It would overwrite individual loadgen. */
	for (ln = 0; ln <= 3; ln++) {
		val = I915_READ(ICL_PORT_TX_DW4_LN(ln, phy));
		val &= ~(POST_CURSOR_1_MASK | POST_CURSOR_2_MASK |
			 CURSOR_COEFF_MASK);
		val |= POST_CURSOR_1(ddi_translations[level].dw4_post_cursor_1);
		val |= POST_CURSOR_2(ddi_translations[level].dw4_post_cursor_2);
		val |= CURSOR_COEFF(ddi_translations[level].dw4_cursor_coeff);
		I915_WRITE(ICL_PORT_TX_DW4_LN(ln, phy), val);
	}

	/* Program PORT_TX_DW7 */
	val = I915_READ(ICL_PORT_TX_DW7_LN0(phy));
	val &= ~N_SCALAR_MASK;
	val |= N_SCALAR(ddi_translations[level].dw7_n_scalar);
	I915_WRITE(ICL_PORT_TX_DW7_GRP(phy), val);
}