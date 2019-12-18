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
typedef  int u32 ;
struct v4l2_subdev {int /*<<< orphan*/  name; } ;
struct v4l2_dv_timings {int dummy; } ;
struct adv7842_state {int cec_valid_addrs; char const* const* cec_addr; size_t rgb_quantization_range; struct v4l2_dv_timings timings; scalar_t__ hdmi_port_a; scalar_t__ cec_enabled_adap; } ;

/* Variables and functions */
 int ADV7842_MAX_ADDRS ; 
 int /*<<< orphan*/  adv7842_log_infoframes (struct v4l2_subdev*) ; 
 scalar_t__ adv7842_query_dv_timings (struct v4l2_subdev*,struct v4l2_dv_timings*) ; 
 int cp_read (struct v4l2_subdev*,int) ; 
 int hdmi_read (struct v4l2_subdev*,int) ; 
 int io_read (struct v4l2_subdev*,int) ; 
 int /*<<< orphan*/  is_digital_input (struct v4l2_subdev*) ; 
 scalar_t__ is_hdmi (struct v4l2_subdev*) ; 
 scalar_t__ no_cp_signal (struct v4l2_subdev*) ; 
 scalar_t__ no_power (struct v4l2_subdev*) ; 
 int rep_read (struct v4l2_subdev*,int) ; 
 struct adv7842_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,...) ; 
 int /*<<< orphan*/  v4l2_print_dv_timings (int /*<<< orphan*/ ,char*,struct v4l2_dv_timings*,int) ; 

__attribute__((used)) static int adv7842_cp_log_status(struct v4l2_subdev *sd)
{
	/* CP block */
	struct adv7842_state *state = to_state(sd);
	struct v4l2_dv_timings timings;
	u8 reg_io_0x02 = io_read(sd, 0x02);
	u8 reg_io_0x21 = io_read(sd, 0x21);
	u8 reg_rep_0x77 = rep_read(sd, 0x77);
	u8 reg_rep_0x7d = rep_read(sd, 0x7d);
	bool audio_pll_locked = hdmi_read(sd, 0x04) & 0x01;
	bool audio_sample_packet_detect = hdmi_read(sd, 0x18) & 0x01;
	bool audio_mute = io_read(sd, 0x65) & 0x40;

	static const char * const csc_coeff_sel_rb[16] = {
		"bypassed", "YPbPr601 -> RGB", "reserved", "YPbPr709 -> RGB",
		"reserved", "RGB -> YPbPr601", "reserved", "RGB -> YPbPr709",
		"reserved", "YPbPr709 -> YPbPr601", "YPbPr601 -> YPbPr709",
		"reserved", "reserved", "reserved", "reserved", "manual"
	};
	static const char * const input_color_space_txt[16] = {
		"RGB limited range (16-235)", "RGB full range (0-255)",
		"YCbCr Bt.601 (16-235)", "YCbCr Bt.709 (16-235)",
		"xvYCC Bt.601", "xvYCC Bt.709",
		"YCbCr Bt.601 (0-255)", "YCbCr Bt.709 (0-255)",
		"invalid", "invalid", "invalid", "invalid", "invalid",
		"invalid", "invalid", "automatic"
	};
	static const char * const rgb_quantization_range_txt[] = {
		"Automatic",
		"RGB limited range (16-235)",
		"RGB full range (0-255)",
	};
	static const char * const deep_color_mode_txt[4] = {
		"8-bits per channel",
		"10-bits per channel",
		"12-bits per channel",
		"16-bits per channel (not supported)"
	};

	v4l2_info(sd, "-----Chip status-----\n");
	v4l2_info(sd, "Chip power: %s\n", no_power(sd) ? "off" : "on");
	v4l2_info(sd, "HDMI/DVI-D port selected: %s\n",
			state->hdmi_port_a ? "A" : "B");
	v4l2_info(sd, "EDID A %s, B %s\n",
		  ((reg_rep_0x7d & 0x04) && (reg_rep_0x77 & 0x04)) ?
		  "enabled" : "disabled",
		  ((reg_rep_0x7d & 0x08) && (reg_rep_0x77 & 0x08)) ?
		  "enabled" : "disabled");
	v4l2_info(sd, "HPD A %s, B %s\n",
		  reg_io_0x21 & 0x02 ? "enabled" : "disabled",
		  reg_io_0x21 & 0x01 ? "enabled" : "disabled");
	v4l2_info(sd, "CEC: %s\n", state->cec_enabled_adap ?
			"enabled" : "disabled");
	if (state->cec_enabled_adap) {
		int i;

		for (i = 0; i < ADV7842_MAX_ADDRS; i++) {
			bool is_valid = state->cec_valid_addrs & (1 << i);

			if (is_valid)
				v4l2_info(sd, "CEC Logical Address: 0x%x\n",
					  state->cec_addr[i]);
		}
	}

	v4l2_info(sd, "-----Signal status-----\n");
	if (state->hdmi_port_a) {
		v4l2_info(sd, "Cable detected (+5V power): %s\n",
			  io_read(sd, 0x6f) & 0x02 ? "true" : "false");
		v4l2_info(sd, "TMDS signal detected: %s\n",
			  (io_read(sd, 0x6a) & 0x02) ? "true" : "false");
		v4l2_info(sd, "TMDS signal locked: %s\n",
			  (io_read(sd, 0x6a) & 0x20) ? "true" : "false");
	} else {
		v4l2_info(sd, "Cable detected (+5V power):%s\n",
			  io_read(sd, 0x6f) & 0x01 ? "true" : "false");
		v4l2_info(sd, "TMDS signal detected: %s\n",
			  (io_read(sd, 0x6a) & 0x01) ? "true" : "false");
		v4l2_info(sd, "TMDS signal locked: %s\n",
			  (io_read(sd, 0x6a) & 0x10) ? "true" : "false");
	}
	v4l2_info(sd, "CP free run: %s\n",
		  (!!(cp_read(sd, 0xff) & 0x10) ? "on" : "off"));
	v4l2_info(sd, "Prim-mode = 0x%x, video std = 0x%x, v_freq = 0x%x\n",
		  io_read(sd, 0x01) & 0x0f, io_read(sd, 0x00) & 0x3f,
		  (io_read(sd, 0x01) & 0x70) >> 4);

	v4l2_info(sd, "-----Video Timings-----\n");
	if (no_cp_signal(sd)) {
		v4l2_info(sd, "STDI: not locked\n");
	} else {
		u32 bl = ((cp_read(sd, 0xb1) & 0x3f) << 8) | cp_read(sd, 0xb2);
		u32 lcf = ((cp_read(sd, 0xb3) & 0x7) << 8) | cp_read(sd, 0xb4);
		u32 lcvs = cp_read(sd, 0xb3) >> 3;
		u32 fcl = ((cp_read(sd, 0xb8) & 0x1f) << 8) | cp_read(sd, 0xb9);
		char hs_pol = ((cp_read(sd, 0xb5) & 0x10) ?
				((cp_read(sd, 0xb5) & 0x08) ? '+' : '-') : 'x');
		char vs_pol = ((cp_read(sd, 0xb5) & 0x40) ?
				((cp_read(sd, 0xb5) & 0x20) ? '+' : '-') : 'x');
		v4l2_info(sd,
			"STDI: lcf (frame height - 1) = %d, bl = %d, lcvs (vsync) = %d, fcl = %d, %s, %chsync, %cvsync\n",
			lcf, bl, lcvs, fcl,
			(cp_read(sd, 0xb1) & 0x40) ?
				"interlaced" : "progressive",
			hs_pol, vs_pol);
	}
	if (adv7842_query_dv_timings(sd, &timings))
		v4l2_info(sd, "No video detected\n");
	else
		v4l2_print_dv_timings(sd->name, "Detected format: ",
				      &timings, true);
	v4l2_print_dv_timings(sd->name, "Configured format: ",
			&state->timings, true);

	if (no_cp_signal(sd))
		return 0;

	v4l2_info(sd, "-----Color space-----\n");
	v4l2_info(sd, "RGB quantization range ctrl: %s\n",
		  rgb_quantization_range_txt[state->rgb_quantization_range]);
	v4l2_info(sd, "Input color space: %s\n",
		  input_color_space_txt[reg_io_0x02 >> 4]);
	v4l2_info(sd, "Output color space: %s %s, alt-gamma %s\n",
		  (reg_io_0x02 & 0x02) ? "RGB" : "YCbCr",
		  (((reg_io_0x02 >> 2) & 0x01) ^ (reg_io_0x02 & 0x01)) ?
			"(16-235)" : "(0-255)",
		  (reg_io_0x02 & 0x08) ? "enabled" : "disabled");
	v4l2_info(sd, "Color space conversion: %s\n",
		  csc_coeff_sel_rb[cp_read(sd, 0xf4) >> 4]);

	if (!is_digital_input(sd))
		return 0;

	v4l2_info(sd, "-----%s status-----\n", is_hdmi(sd) ? "HDMI" : "DVI-D");
	v4l2_info(sd, "HDCP encrypted content: %s\n",
			(hdmi_read(sd, 0x05) & 0x40) ? "true" : "false");
	v4l2_info(sd, "HDCP keys read: %s%s\n",
			(hdmi_read(sd, 0x04) & 0x20) ? "yes" : "no",
			(hdmi_read(sd, 0x04) & 0x10) ? "ERROR" : "");
	if (!is_hdmi(sd))
		return 0;

	v4l2_info(sd, "Audio: pll %s, samples %s, %s\n",
			audio_pll_locked ? "locked" : "not locked",
			audio_sample_packet_detect ? "detected" : "not detected",
			audio_mute ? "muted" : "enabled");
	if (audio_pll_locked && audio_sample_packet_detect) {
		v4l2_info(sd, "Audio format: %s\n",
			(hdmi_read(sd, 0x07) & 0x40) ? "multi-channel" : "stereo");
	}
	v4l2_info(sd, "Audio CTS: %u\n", (hdmi_read(sd, 0x5b) << 12) +
			(hdmi_read(sd, 0x5c) << 8) +
			(hdmi_read(sd, 0x5d) & 0xf0));
	v4l2_info(sd, "Audio N: %u\n", ((hdmi_read(sd, 0x5d) & 0x0f) << 16) +
			(hdmi_read(sd, 0x5e) << 8) +
			hdmi_read(sd, 0x5f));
	v4l2_info(sd, "AV Mute: %s\n",
			(hdmi_read(sd, 0x04) & 0x40) ? "on" : "off");
	v4l2_info(sd, "Deep color mode: %s\n",
			deep_color_mode_txt[hdmi_read(sd, 0x0b) >> 6]);

	adv7842_log_infoframes(sd);

	return 0;
}