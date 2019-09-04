#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tv_mode {int mode; int chroma_freq; TYPE_4__* resync_params; int /*<<< orphan*/  vblank_level; TYPE_3__* color_gains; TYPE_2__* burst_levels; TYPE_1__* video_levels; int /*<<< orphan*/  line_number; int /*<<< orphan*/  front_porch; int /*<<< orphan*/  back_porch; scalar_t__ dac_bit25_en; scalar_t__ dac3_en; scalar_t__ yc_en; } ;
struct sun4i_tv {int /*<<< orphan*/  regs; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int dummy; } ;
struct TYPE_8__ {scalar_t__ field; int /*<<< orphan*/  line; int /*<<< orphan*/  pixel; } ;
struct TYPE_7__ {int /*<<< orphan*/  cr; int /*<<< orphan*/  cb; } ;
struct TYPE_6__ {int /*<<< orphan*/  cr; int /*<<< orphan*/  cb; } ;
struct TYPE_5__ {int /*<<< orphan*/  black; int /*<<< orphan*/  blank; } ;

/* Variables and functions */
 int BIT (int) ; 
 int SUN4I_TVE_12C_COMP_YUV_EN ; 
 int SUN4I_TVE_12C_NOTCH_WIDTH_WIDE ; 
 int /*<<< orphan*/  SUN4I_TVE_12C_REG ; 
 int SUN4I_TVE_ACTIVE_LINE (int) ; 
 int /*<<< orphan*/  SUN4I_TVE_ACTIVE_LINE_REG ; 
 int SUN4I_TVE_BURST_WIDTH_BREEZEWAY (int) ; 
 int SUN4I_TVE_BURST_WIDTH_BURST_WIDTH (int) ; 
 int SUN4I_TVE_BURST_WIDTH_HSYNC_WIDTH (int) ; 
 int /*<<< orphan*/  SUN4I_TVE_BURST_WIDTH_REG ; 
 int SUN4I_TVE_CB_CR_GAIN_CB (int /*<<< orphan*/ ) ; 
 int SUN4I_TVE_CB_CR_GAIN_CR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN4I_TVE_CB_CR_GAIN_REG ; 
 int SUN4I_TVE_CB_CR_LVL_CB_BURST (int /*<<< orphan*/ ) ; 
 int SUN4I_TVE_CB_CR_LVL_CR_BURST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN4I_TVE_CB_CR_LVL_REG ; 
 int SUN4I_TVE_CFG0_COMP_EN ; 
 int SUN4I_TVE_CFG0_CORE_CONTROL_54M ; 
 int SUN4I_TVE_CFG0_CORE_DATAPATH_54M ; 
 int SUN4I_TVE_CFG0_DAC_CONTROL_54M ; 
 int /*<<< orphan*/  SUN4I_TVE_CFG0_REG ; 
 int SUN4I_TVE_CFG0_YC_EN ; 
 int SUN4I_TVE_CHROMA_COMP_GAIN_50 ; 
 int /*<<< orphan*/  SUN4I_TVE_CHROMA_FREQ_REG ; 
 int /*<<< orphan*/  SUN4I_TVE_CHROMA_REG ; 
 int SUN4I_TVE_DAC0_CHROMA_0_75 ; 
 int SUN4I_TVE_DAC0_CLOCK_INVERT ; 
 int SUN4I_TVE_DAC0_DAC_EN (int) ; 
 int SUN4I_TVE_DAC0_INTERNAL_DAC_37_5_OHMS ; 
 int SUN4I_TVE_DAC0_LUMA_0_4 ; 
 int /*<<< orphan*/  SUN4I_TVE_DAC0_REG ; 
 int SUN4I_TVE_DAC1_AMPLITUDE (int,int) ; 
 int /*<<< orphan*/  SUN4I_TVE_DAC1_REG ; 
 int SUN4I_TVE_EN_DAC_MAP (int,int) ; 
 int /*<<< orphan*/  SUN4I_TVE_EN_DAC_MAP_MASK ; 
 int /*<<< orphan*/  SUN4I_TVE_EN_REG ; 
 int SUN4I_TVE_LEVEL_BLACK (int /*<<< orphan*/ ) ; 
 int SUN4I_TVE_LEVEL_BLANK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN4I_TVE_LEVEL_REG ; 
 int SUN4I_TVE_LINE_FIRST (int) ; 
 int SUN4I_TVE_LINE_NUMBER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN4I_TVE_LINE_REG ; 
 int SUN4I_TVE_NOTCH_DAC0_TO_DAC_DLY (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN4I_TVE_NOTCH_REG ; 
 int SUN4I_TVE_PORCH_BACK (int /*<<< orphan*/ ) ; 
 int SUN4I_TVE_PORCH_FRONT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN4I_TVE_PORCH_REG ; 
 int SUN4I_TVE_RESYNC_FIELD ; 
 int SUN4I_TVE_RESYNC_LINE (int /*<<< orphan*/ ) ; 
 int SUN4I_TVE_RESYNC_PIXEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN4I_TVE_RESYNC_REG ; 
 int /*<<< orphan*/  SUN4I_TVE_SLAVE_REG ; 
 int /*<<< orphan*/  SUN4I_TVE_SYNC_VBI_REG ; 
 int SUN4I_TVE_SYNC_VBI_SYNC (int) ; 
 int SUN4I_TVE_SYNC_VBI_VBLANK (int /*<<< orphan*/ ) ; 
 struct sun4i_tv* drm_encoder_to_sun4i_tv (struct drm_encoder*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct tv_mode* sun4i_tv_find_tv_by_mode (struct drm_display_mode*) ; 

__attribute__((used)) static void sun4i_tv_mode_set(struct drm_encoder *encoder,
			      struct drm_display_mode *mode,
			      struct drm_display_mode *adjusted_mode)
{
	struct sun4i_tv *tv = drm_encoder_to_sun4i_tv(encoder);
	const struct tv_mode *tv_mode = sun4i_tv_find_tv_by_mode(mode);

	/* Enable and map the DAC to the output */
	regmap_update_bits(tv->regs, SUN4I_TVE_EN_REG,
			   SUN4I_TVE_EN_DAC_MAP_MASK,
			   SUN4I_TVE_EN_DAC_MAP(0, 1) |
			   SUN4I_TVE_EN_DAC_MAP(1, 2) |
			   SUN4I_TVE_EN_DAC_MAP(2, 3) |
			   SUN4I_TVE_EN_DAC_MAP(3, 4));

	/* Set PAL settings */
	regmap_write(tv->regs, SUN4I_TVE_CFG0_REG,
		     tv_mode->mode |
		     (tv_mode->yc_en ? SUN4I_TVE_CFG0_YC_EN : 0) |
		     SUN4I_TVE_CFG0_COMP_EN |
		     SUN4I_TVE_CFG0_DAC_CONTROL_54M |
		     SUN4I_TVE_CFG0_CORE_DATAPATH_54M |
		     SUN4I_TVE_CFG0_CORE_CONTROL_54M);

	/* Configure the DAC for a composite output */
	regmap_write(tv->regs, SUN4I_TVE_DAC0_REG,
		     SUN4I_TVE_DAC0_DAC_EN(0) |
		     (tv_mode->dac3_en ? SUN4I_TVE_DAC0_DAC_EN(3) : 0) |
		     SUN4I_TVE_DAC0_INTERNAL_DAC_37_5_OHMS |
		     SUN4I_TVE_DAC0_CHROMA_0_75 |
		     SUN4I_TVE_DAC0_LUMA_0_4 |
		     SUN4I_TVE_DAC0_CLOCK_INVERT |
		     (tv_mode->dac_bit25_en ? BIT(25) : 0) |
		     BIT(30));

	/* Configure the sample delay between DAC0 and the other DAC */
	regmap_write(tv->regs, SUN4I_TVE_NOTCH_REG,
		     SUN4I_TVE_NOTCH_DAC0_TO_DAC_DLY(1, 0) |
		     SUN4I_TVE_NOTCH_DAC0_TO_DAC_DLY(2, 0));

	regmap_write(tv->regs, SUN4I_TVE_CHROMA_FREQ_REG,
		     tv_mode->chroma_freq);

	/* Set the front and back porch */
	regmap_write(tv->regs, SUN4I_TVE_PORCH_REG,
		     SUN4I_TVE_PORCH_BACK(tv_mode->back_porch) |
		     SUN4I_TVE_PORCH_FRONT(tv_mode->front_porch));

	/* Set the lines setup */
	regmap_write(tv->regs, SUN4I_TVE_LINE_REG,
		     SUN4I_TVE_LINE_FIRST(22) |
		     SUN4I_TVE_LINE_NUMBER(tv_mode->line_number));

	regmap_write(tv->regs, SUN4I_TVE_LEVEL_REG,
		     SUN4I_TVE_LEVEL_BLANK(tv_mode->video_levels->blank) |
		     SUN4I_TVE_LEVEL_BLACK(tv_mode->video_levels->black));

	regmap_write(tv->regs, SUN4I_TVE_DAC1_REG,
		     SUN4I_TVE_DAC1_AMPLITUDE(0, 0x18) |
		     SUN4I_TVE_DAC1_AMPLITUDE(1, 0x18) |
		     SUN4I_TVE_DAC1_AMPLITUDE(2, 0x18) |
		     SUN4I_TVE_DAC1_AMPLITUDE(3, 0x18));

	regmap_write(tv->regs, SUN4I_TVE_CB_CR_LVL_REG,
		     SUN4I_TVE_CB_CR_LVL_CB_BURST(tv_mode->burst_levels->cb) |
		     SUN4I_TVE_CB_CR_LVL_CR_BURST(tv_mode->burst_levels->cr));

	/* Set burst width for a composite output */
	regmap_write(tv->regs, SUN4I_TVE_BURST_WIDTH_REG,
		     SUN4I_TVE_BURST_WIDTH_HSYNC_WIDTH(126) |
		     SUN4I_TVE_BURST_WIDTH_BURST_WIDTH(68) |
		     SUN4I_TVE_BURST_WIDTH_BREEZEWAY(22));

	regmap_write(tv->regs, SUN4I_TVE_CB_CR_GAIN_REG,
		     SUN4I_TVE_CB_CR_GAIN_CB(tv_mode->color_gains->cb) |
		     SUN4I_TVE_CB_CR_GAIN_CR(tv_mode->color_gains->cr));

	regmap_write(tv->regs, SUN4I_TVE_SYNC_VBI_REG,
		     SUN4I_TVE_SYNC_VBI_SYNC(0x10) |
		     SUN4I_TVE_SYNC_VBI_VBLANK(tv_mode->vblank_level));

	regmap_write(tv->regs, SUN4I_TVE_ACTIVE_LINE_REG,
		     SUN4I_TVE_ACTIVE_LINE(1440));

	/* Set composite chroma gain to 50 % */
	regmap_write(tv->regs, SUN4I_TVE_CHROMA_REG,
		     SUN4I_TVE_CHROMA_COMP_GAIN_50);

	regmap_write(tv->regs, SUN4I_TVE_12C_REG,
		     SUN4I_TVE_12C_COMP_YUV_EN |
		     SUN4I_TVE_12C_NOTCH_WIDTH_WIDE);

	regmap_write(tv->regs, SUN4I_TVE_RESYNC_REG,
		     SUN4I_TVE_RESYNC_PIXEL(tv_mode->resync_params->pixel) |
		     SUN4I_TVE_RESYNC_LINE(tv_mode->resync_params->line) |
		     (tv_mode->resync_params->field ?
		      SUN4I_TVE_RESYNC_FIELD : 0));

	regmap_write(tv->regs, SUN4I_TVE_SLAVE_REG, 0);
}