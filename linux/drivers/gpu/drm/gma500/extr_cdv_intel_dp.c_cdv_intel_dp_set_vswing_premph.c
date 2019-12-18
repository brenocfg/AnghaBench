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
typedef  int uint8_t ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct gma_encoder {struct cdv_intel_dp* dev_priv; TYPE_1__ base; } ;
struct drm_device {int dummy; } ;
struct ddi_regoff {int /*<<< orphan*/  PreEmph2; int /*<<< orphan*/  PreEmph1; int /*<<< orphan*/  VSwing1; int /*<<< orphan*/  VSwing3; int /*<<< orphan*/  VSwing2; int /*<<< orphan*/  VSwing5; } ;
struct cdv_intel_dp {scalar_t__ output_reg; } ;

/* Variables and functions */
 scalar_t__ DP_B ; 
 int DP_TRAIN_PRE_EMPHASIS_MASK ; 
 int DP_TRAIN_PRE_EMPHASIS_SHIFT ; 
 int DP_TRAIN_VOLTAGE_SWING_LEVEL_3 ; 
 int DP_TRAIN_VOLTAGE_SWING_MASK ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  cdv_sb_reset (struct drm_device*) ; 
 int /*<<< orphan*/  cdv_sb_write (struct drm_device*,int /*<<< orphan*/ ,int) ; 
 struct ddi_regoff* ddi_DP_train_table ; 
 int* dp_vswing_premph_table ; 

__attribute__((used)) static void
cdv_intel_dp_set_vswing_premph(struct gma_encoder *encoder, uint8_t signal_level)
{
	struct drm_device *dev = encoder->base.dev;
	struct cdv_intel_dp *intel_dp = encoder->dev_priv;
	struct ddi_regoff *ddi_reg;
	int vswing, premph, index;

	if (intel_dp->output_reg == DP_B)
		ddi_reg = &ddi_DP_train_table[0];
	else
		ddi_reg = &ddi_DP_train_table[1];

	vswing = (signal_level & DP_TRAIN_VOLTAGE_SWING_MASK);
	premph = ((signal_level & DP_TRAIN_PRE_EMPHASIS_MASK)) >>
				DP_TRAIN_PRE_EMPHASIS_SHIFT;

	if (vswing + premph > 3)
		return;
#ifdef CDV_FAST_LINK_TRAIN
	return;
#endif
	DRM_DEBUG_KMS("Test2\n");
	//return ;
	cdv_sb_reset(dev);
	/* ;Swing voltage programming
        ;gfx_dpio_set_reg(0xc058, 0x0505313A) */
	cdv_sb_write(dev, ddi_reg->VSwing5, 0x0505313A);

	/* ;gfx_dpio_set_reg(0x8154, 0x43406055) */
	cdv_sb_write(dev, ddi_reg->VSwing1, 0x43406055);

	/* ;gfx_dpio_set_reg(0x8148, 0x55338954)
	 * The VSwing_PreEmph table is also considered based on the vswing/premp
	 */
	index = (vswing + premph) * 2;
	if (premph == 1 && vswing == 1) {
		cdv_sb_write(dev, ddi_reg->VSwing2, 0x055738954);
	} else
		cdv_sb_write(dev, ddi_reg->VSwing2, dp_vswing_premph_table[index]);

	/* ;gfx_dpio_set_reg(0x814c, 0x40802040) */
	if ((vswing + premph) == DP_TRAIN_VOLTAGE_SWING_LEVEL_3)
		cdv_sb_write(dev, ddi_reg->VSwing3, 0x70802040);
	else
		cdv_sb_write(dev, ddi_reg->VSwing3, 0x40802040);

	/* ;gfx_dpio_set_reg(0x8150, 0x2b405555) */
	/* cdv_sb_write(dev, ddi_reg->VSwing4, 0x2b405555); */

	/* ;gfx_dpio_set_reg(0x8154, 0xc3406055) */
	cdv_sb_write(dev, ddi_reg->VSwing1, 0xc3406055);

	/* ;Pre emphasis programming
	 * ;gfx_dpio_set_reg(0xc02c, 0x1f030040)
	 */
	cdv_sb_write(dev, ddi_reg->PreEmph1, 0x1f030040);

	/* ;gfx_dpio_set_reg(0x8124, 0x00004000) */
	index = 2 * premph + 1;
	cdv_sb_write(dev, ddi_reg->PreEmph2, dp_vswing_premph_table[index]);
	return;	
}