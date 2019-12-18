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
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct tda1997x_platform_data {int vidout_delay_pclk; int vidout_inv_pclk; int vidout_delay_vs; int vidout_delay_hs; int vidout_delay_de; int vidout_inv_de; int vidout_sel_de; int vidout_inv_hs; int vidout_sel_hs; int vidout_inv_vs; int vidout_sel_vs; } ;
struct tda1997x_state {int vid_fmt; struct tda1997x_platform_data pdata; struct v4l2_subdev sd; } ;

/* Variables and functions */
 int DE_FREF_DELAY_SHIFT ; 
 int DE_FREF_INV_SHIFT ; 
 int DE_FREF_SEL_SHIFT ; 
 int FILTERS_CTRL_2_7TAP ; 
 int FILTERS_CTRL_BU_SHIFT ; 
 int FILTERS_CTRL_RV_SHIFT ; 
 int HS_HREF_DELAY_SHIFT ; 
 int HS_HREF_INV_SHIFT ; 
 int HS_HREF_SEL_NONE ; 
 int HS_HREF_SEL_SHIFT ; 
 int OF_BLK ; 
 int OF_FMT_422_CCIR ; 
 int OF_FMT_422_SMPT ; 
 int OF_FMT_444 ; 
 int OF_FMT_MASK ; 
 int OF_TRC ; 
 int OF_VP_ENABLE ; 
 int PCLK_DELAY_SHIFT ; 
 int PCLK_INV_SHIFT ; 
 int PCLK_SEL_X1 ; 
 int PCLK_SEL_X2 ; 
 int /*<<< orphan*/  REG_DE_FREF ; 
 int /*<<< orphan*/  REG_FILTERS_CTRL ; 
 int /*<<< orphan*/  REG_HS_HREF ; 
 int /*<<< orphan*/  REG_OF ; 
 int /*<<< orphan*/  REG_PCLK ; 
 int /*<<< orphan*/  REG_VDP_CTRL ; 
 int /*<<< orphan*/  REG_VS_VREF ; 
 int VDP_CTRL_COMPDEL_BP ; 
 int VDP_CTRL_FORMATTER_BP ; 
 int VDP_CTRL_PREFILTER_BP ; 
 int VS_VREF_DELAY_SHIFT ; 
 int VS_VREF_INV_SHIFT ; 
 int VS_VREF_SEL_NONE ; 
 int VS_VREF_SEL_SHIFT ; 
 int io_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
tda1997x_configure_vidout(struct tda1997x_state *state)
{
	struct v4l2_subdev *sd = &state->sd;
	struct tda1997x_platform_data *pdata = &state->pdata;
	u8 prefilter;
	u8 reg;

	/* Configure pixel clock generator: delay, polarity, rate */
	reg = (state->vid_fmt == OF_FMT_422_CCIR) ?
	       PCLK_SEL_X2 : PCLK_SEL_X1;
	reg |= pdata->vidout_delay_pclk << PCLK_DELAY_SHIFT;
	reg |= pdata->vidout_inv_pclk << PCLK_INV_SHIFT;
	io_write(sd, REG_PCLK, reg);

	/* Configure pre-filter */
	prefilter = 0; /* filters off */
	/* YUV422 mode requires conversion */
	if ((state->vid_fmt == OF_FMT_422_SMPT) ||
	    (state->vid_fmt == OF_FMT_422_CCIR)) {
		/* 2/7 taps for Rv and Bu */
		prefilter = FILTERS_CTRL_2_7TAP << FILTERS_CTRL_BU_SHIFT |
			    FILTERS_CTRL_2_7TAP << FILTERS_CTRL_RV_SHIFT;
	}
	io_write(sd, REG_FILTERS_CTRL, prefilter);

	/* Configure video port */
	reg = state->vid_fmt & OF_FMT_MASK;
	if (state->vid_fmt == OF_FMT_422_CCIR)
		reg |= (OF_BLK | OF_TRC);
	reg |= OF_VP_ENABLE;
	io_write(sd, REG_OF, reg);

	/* Configure formatter and conversions */
	reg = io_read(sd, REG_VDP_CTRL);
	/* pre-filter is needed unless (REG_FILTERS_CTRL == 0) */
	if (!prefilter)
		reg |= VDP_CTRL_PREFILTER_BP;
	else
		reg &= ~VDP_CTRL_PREFILTER_BP;
	/* formatter is needed for YUV422 and for trc/blc codes */
	if (state->vid_fmt == OF_FMT_444)
		reg |= VDP_CTRL_FORMATTER_BP;
	/* formatter and compdel needed for timing/blanking codes */
	else
		reg &= ~(VDP_CTRL_FORMATTER_BP | VDP_CTRL_COMPDEL_BP);
	/* activate compdel for small sync delays */
	if ((pdata->vidout_delay_vs < 4) || (pdata->vidout_delay_hs < 4))
		reg &= ~VDP_CTRL_COMPDEL_BP;
	io_write(sd, REG_VDP_CTRL, reg);

	/* Configure DE output signal: delay, polarity, and source */
	reg = pdata->vidout_delay_de << DE_FREF_DELAY_SHIFT |
	      pdata->vidout_inv_de << DE_FREF_INV_SHIFT |
	      pdata->vidout_sel_de << DE_FREF_SEL_SHIFT;
	io_write(sd, REG_DE_FREF, reg);

	/* Configure HS/HREF output signal: delay, polarity, and source */
	if (state->vid_fmt != OF_FMT_422_CCIR) {
		reg = pdata->vidout_delay_hs << HS_HREF_DELAY_SHIFT |
		      pdata->vidout_inv_hs << HS_HREF_INV_SHIFT |
		      pdata->vidout_sel_hs << HS_HREF_SEL_SHIFT;
	} else
		reg = HS_HREF_SEL_NONE << HS_HREF_SEL_SHIFT;
	io_write(sd, REG_HS_HREF, reg);

	/* Configure VS/VREF output signal: delay, polarity, and source */
	if (state->vid_fmt != OF_FMT_422_CCIR) {
		reg = pdata->vidout_delay_vs << VS_VREF_DELAY_SHIFT |
		      pdata->vidout_inv_vs << VS_VREF_INV_SHIFT |
		      pdata->vidout_sel_vs << VS_VREF_SEL_SHIFT;
	} else
		reg = VS_VREF_SEL_NONE << VS_VREF_SEL_SHIFT;
	io_write(sd, REG_VS_VREF, reg);

	return 0;
}