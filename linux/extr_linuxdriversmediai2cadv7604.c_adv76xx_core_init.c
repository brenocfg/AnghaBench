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
struct v4l2_subdev {int /*<<< orphan*/  ctrl_handler; } ;
struct adv76xx_platform_data {scalar_t__ default_input; int alt_gamma; int blank_data; int insert_av_codes; int replicate_av_codes; int inv_vs_pol; int inv_hs_pol; int inv_llc_pol; int dr_str_data; int dr_str_clk; int dr_str_sync; int hdmi_free_run_mode; int ain_sel; int output_bus_lsb_to_msb; int int1_config; scalar_t__ disable_cable_det_rst; scalar_t__ disable_pwrdnb; } ;
struct adv76xx_state {scalar_t__ source_pad; scalar_t__ selected_input; struct adv76xx_platform_data pdata; struct adv76xx_chip_info* info; } ;
struct adv76xx_chip_info {int fmt_change_digital_mask; int cable_det_mask; int /*<<< orphan*/  (* setup_irqs ) (struct v4l2_subdev*) ;} ;

/* Variables and functions */
 scalar_t__ adv76xx_has_afe (struct adv76xx_state*) ; 
 int /*<<< orphan*/  adv76xx_setup_format (struct adv76xx_state*) ; 
 int /*<<< orphan*/  afe_write (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  cp_write (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  disable_input (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  enable_input (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  hdmi_write (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  hdmi_write_clr_set (struct v4l2_subdev*,int,int,int) ; 
 int /*<<< orphan*/  io_write (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  io_write_clr_set (struct v4l2_subdev*,int,int,int) ; 
 int /*<<< orphan*/  select_input (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  stub1 (struct v4l2_subdev*) ; 
 struct adv76xx_state* to_state (struct v4l2_subdev*) ; 
 int v4l2_ctrl_handler_setup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adv76xx_core_init(struct v4l2_subdev *sd)
{
	struct adv76xx_state *state = to_state(sd);
	const struct adv76xx_chip_info *info = state->info;
	struct adv76xx_platform_data *pdata = &state->pdata;

	hdmi_write(sd, 0x48,
		(pdata->disable_pwrdnb ? 0x80 : 0) |
		(pdata->disable_cable_det_rst ? 0x40 : 0));

	disable_input(sd);

	if (pdata->default_input >= 0 &&
	    pdata->default_input < state->source_pad) {
		state->selected_input = pdata->default_input;
		select_input(sd);
		enable_input(sd);
	}

	/* power */
	io_write(sd, 0x0c, 0x42);   /* Power up part and power down VDP */
	io_write(sd, 0x0b, 0x44);   /* Power down ESDP block */
	cp_write(sd, 0xcf, 0x01);   /* Power down macrovision */

	/* video format */
	io_write_clr_set(sd, 0x02, 0x0f, pdata->alt_gamma << 3);
	io_write_clr_set(sd, 0x05, 0x0e, pdata->blank_data << 3 |
			pdata->insert_av_codes << 2 |
			pdata->replicate_av_codes << 1);
	adv76xx_setup_format(state);

	cp_write(sd, 0x69, 0x30);   /* Enable CP CSC */

	/* VS, HS polarities */
	io_write(sd, 0x06, 0xa0 | pdata->inv_vs_pol << 2 |
		 pdata->inv_hs_pol << 1 | pdata->inv_llc_pol);

	/* Adjust drive strength */
	io_write(sd, 0x14, 0x40 | pdata->dr_str_data << 4 |
				pdata->dr_str_clk << 2 |
				pdata->dr_str_sync);

	cp_write(sd, 0xba, (pdata->hdmi_free_run_mode << 1) | 0x01); /* HDMI free run */
	cp_write(sd, 0xf3, 0xdc); /* Low threshold to enter/exit free run mode */
	cp_write(sd, 0xf9, 0x23); /*  STDI ch. 1 - LCVS change threshold -
				      ADI recommended setting [REF_01, c. 2.3.3] */
	cp_write(sd, 0x45, 0x23); /*  STDI ch. 2 - LCVS change threshold -
				      ADI recommended setting [REF_01, c. 2.3.3] */
	cp_write(sd, 0xc9, 0x2d); /* use prim_mode and vid_std as free run resolution
				     for digital formats */

	/* HDMI audio */
	hdmi_write_clr_set(sd, 0x15, 0x03, 0x03); /* Mute on FIFO over-/underflow [REF_01, c. 1.2.18] */
	hdmi_write_clr_set(sd, 0x1a, 0x0e, 0x08); /* Wait 1 s before unmute */
	hdmi_write_clr_set(sd, 0x68, 0x06, 0x06); /* FIFO reset on over-/underflow [REF_01, c. 1.2.19] */

	/* TODO from platform data */
	afe_write(sd, 0xb5, 0x01);  /* Setting MCLK to 256Fs */

	if (adv76xx_has_afe(state)) {
		afe_write(sd, 0x02, pdata->ain_sel); /* Select analog input muxing mode */
		io_write_clr_set(sd, 0x30, 1 << 4, pdata->output_bus_lsb_to_msb << 4);
	}

	/* interrupts */
	io_write(sd, 0x40, 0xc0 | pdata->int1_config); /* Configure INT1 */
	io_write(sd, 0x46, 0x98); /* Enable SSPD, STDI and CP unlocked interrupts */
	io_write(sd, 0x6e, info->fmt_change_digital_mask); /* Enable V_LOCKED and DE_REGEN_LCK interrupts */
	io_write(sd, 0x73, info->cable_det_mask); /* Enable cable detection (+5v) interrupts */
	info->setup_irqs(sd);

	return v4l2_ctrl_handler_setup(sd->ctrl_handler);
}