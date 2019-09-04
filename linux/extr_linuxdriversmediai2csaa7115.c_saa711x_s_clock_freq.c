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
typedef  int u64 ;
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct saa711x_state {int std; int cgcdiv; int double_asclk; int audclk_freq; scalar_t__ apll; scalar_t__ ucgc; int /*<<< orphan*/  crystal_freq; int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ R_30_AUD_MAST_CLK_CYCLES_PER_FIELD ; 
 scalar_t__ R_34_AUD_MAST_CLK_NOMINAL_INC ; 
 scalar_t__ R_38_CLK_RATIO_AMXCLK_TO_ASCLK ; 
 scalar_t__ R_39_CLK_RATIO_ASCLK_TO_ALRCLK ; 
 scalar_t__ R_3A_AUD_CLK_GEN_BASIC_SETUP ; 
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa711x_has_reg (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  saa711x_write (struct v4l2_subdev*,scalar_t__,int) ; 
 struct saa711x_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int) ; 

__attribute__((used)) static int saa711x_s_clock_freq(struct v4l2_subdev *sd, u32 freq)
{
	struct saa711x_state *state = to_state(sd);
	u32 acpf;
	u32 acni;
	u32 hz;
	u64 f;
	u8 acc = 0;	/* reg 0x3a, audio clock control */

	/* Checks for chips that don't have audio clock (saa7111, saa7113) */
	if (!saa711x_has_reg(state->ident, R_30_AUD_MAST_CLK_CYCLES_PER_FIELD))
		return 0;

	v4l2_dbg(1, debug, sd, "set audio clock freq: %d\n", freq);

	/* sanity check */
	if (freq < 32000 || freq > 48000)
		return -EINVAL;

	/* hz is the refresh rate times 100 */
	hz = (state->std & V4L2_STD_525_60) ? 5994 : 5000;
	/* acpf = (256 * freq) / field_frequency == (256 * 100 * freq) / hz */
	acpf = (25600 * freq) / hz;
	/* acni = (256 * freq * 2^23) / crystal_frequency =
		  (freq * 2^(8+23)) / crystal_frequency =
		  (freq << 31) / crystal_frequency */
	f = freq;
	f = f << 31;
	do_div(f, state->crystal_freq);
	acni = f;
	if (state->ucgc) {
		acpf = acpf * state->cgcdiv / 16;
		acni = acni * state->cgcdiv / 16;
		acc = 0x80;
		if (state->cgcdiv == 3)
			acc |= 0x40;
	}
	if (state->apll)
		acc |= 0x08;

	if (state->double_asclk) {
		acpf <<= 1;
		acni <<= 1;
	}
	saa711x_write(sd, R_38_CLK_RATIO_AMXCLK_TO_ASCLK, 0x03);
	saa711x_write(sd, R_39_CLK_RATIO_ASCLK_TO_ALRCLK, 0x10 << state->double_asclk);
	saa711x_write(sd, R_3A_AUD_CLK_GEN_BASIC_SETUP, acc);

	saa711x_write(sd, R_30_AUD_MAST_CLK_CYCLES_PER_FIELD, acpf & 0xff);
	saa711x_write(sd, R_30_AUD_MAST_CLK_CYCLES_PER_FIELD+1,
							(acpf >> 8) & 0xff);
	saa711x_write(sd, R_30_AUD_MAST_CLK_CYCLES_PER_FIELD+2,
							(acpf >> 16) & 0x03);

	saa711x_write(sd, R_34_AUD_MAST_CLK_NOMINAL_INC, acni & 0xff);
	saa711x_write(sd, R_34_AUD_MAST_CLK_NOMINAL_INC+1, (acni >> 8) & 0xff);
	saa711x_write(sd, R_34_AUD_MAST_CLK_NOMINAL_INC+2, (acni >> 16) & 0x3f);
	state->audclk_freq = freq;
	return 0;
}