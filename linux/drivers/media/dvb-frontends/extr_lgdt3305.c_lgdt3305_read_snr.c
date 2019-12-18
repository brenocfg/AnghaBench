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
typedef  int u32 ;
typedef  int u16 ;
struct lgdt3305_state {int current_modulation; int snr; } ;
struct dvb_frontend {struct lgdt3305_state* demodulator_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LGDT3305_CR_MSE_1 ; 
 int /*<<< orphan*/  LGDT3305_CR_MSE_2 ; 
 int /*<<< orphan*/  LGDT3305_EQ_MSE_1 ; 
 int /*<<< orphan*/  LGDT3305_EQ_MSE_2 ; 
 int /*<<< orphan*/  LGDT3305_EQ_MSE_3 ; 
 int /*<<< orphan*/  LGDT3305_PT_MSE_1 ; 
 int /*<<< orphan*/  LGDT3305_PT_MSE_2 ; 
 int /*<<< orphan*/  LGDT3305_PT_MSE_3 ; 
#define  QAM_256 130 
#define  QAM_64 129 
#define  VSB_8 128 
 int calculate_snr (int,int) ; 
 int /*<<< orphan*/  lg_dbg (char*,int,int,int) ; 
 int read_reg (struct lgdt3305_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lgdt3305_read_snr(struct dvb_frontend *fe, u16 *snr)
{
	struct lgdt3305_state *state = fe->demodulator_priv;
	u32 noise;	/* noise value */
	u32 c;		/* per-modulation SNR calculation constant */

	switch (state->current_modulation) {
	case VSB_8:
#ifdef USE_PTMSE
		/* Use Phase Tracker Mean-Square Error Register */
		/* SNR for ranges from -13.11 to +44.08 */
		noise =	((read_reg(state, LGDT3305_PT_MSE_1) & 0x07) << 16) |
			(read_reg(state, LGDT3305_PT_MSE_2) << 8) |
			(read_reg(state, LGDT3305_PT_MSE_3) & 0xff);
		c = 73957994; /* log10(25*32^2)*2^24 */
#else
		/* Use Equalizer Mean-Square Error Register */
		/* SNR for ranges from -16.12 to +44.08 */
		noise =	((read_reg(state, LGDT3305_EQ_MSE_1) & 0x0f) << 16) |
			(read_reg(state, LGDT3305_EQ_MSE_2) << 8) |
			(read_reg(state, LGDT3305_EQ_MSE_3) & 0xff);
		c = 73957994; /* log10(25*32^2)*2^24 */
#endif
		break;
	case QAM_64:
	case QAM_256:
		noise = (read_reg(state, LGDT3305_CR_MSE_1) << 8) |
			(read_reg(state, LGDT3305_CR_MSE_2) & 0xff);

		c = (state->current_modulation == QAM_64) ?
			97939837 : 98026066;
		/* log10(688128)*2^24 and log10(696320)*2^24 */
		break;
	default:
		return -EINVAL;
	}
	state->snr = calculate_snr(noise, c);
	/* report SNR in dB * 10 */
	*snr = (state->snr / ((1 << 24) / 10));
	lg_dbg("noise = 0x%08x, snr = %d.%02d dB\n", noise,
	       state->snr >> 24, (((state->snr >> 8) & 0xffff) * 100) >> 16);

	return 0;
}