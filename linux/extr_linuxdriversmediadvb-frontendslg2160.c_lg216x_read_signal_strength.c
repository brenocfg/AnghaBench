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
typedef  scalar_t__ u16 ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int lg216x_read_signal_strength(struct dvb_frontend *fe,
				       u16 *strength)
{
#if 0
	/* borrowed from lgdt330x.c
	 *
	 * Calculate strength from SNR up to 35dB
	 * Even though the SNR can go higher than 35dB,
	 * there is some comfort factor in having a range of
	 * strong signals that can show at 100%
	 */
	struct lg216x_state *state = fe->demodulator_priv;
	u16 snr;
	int ret;
#endif
	*strength = 0;
#if 0
	ret = fe->ops.read_snr(fe, &snr);
	if (lg_fail(ret))
		goto fail;
	/* Rather than use the 8.8 value snr, use state->snr which is 8.24 */
	/* scale the range 0 - 35*2^24 into 0 - 65535 */
	if (state->snr >= 8960 * 0x10000)
		*strength = 0xffff;
	else
		*strength = state->snr / 8960;
fail:
	return ret;
#else
	return 0;
#endif
}