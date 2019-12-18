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
typedef  int u16 ;
struct mxl111sf_demod_state {int dummy; } ;
struct dvb_frontend {struct mxl111sf_demod_state* demodulator_priv; } ;
typedef  enum fe_modulation { ____Placeholder_fe_modulation } fe_modulation ;

/* Variables and functions */
 int EINVAL ; 
#define  QAM_16 130 
#define  QAM_64 129 
#define  QPSK 128 
 int min (int,int) ; 
 int mxl111sf_demod_calc_snr (struct mxl111sf_demod_state*,int*) ; 
 int mxl1x1sf_demod_get_tps_modulation (struct mxl111sf_demod_state*,int*) ; 

__attribute__((used)) static int mxl111sf_demod_read_signal_strength(struct dvb_frontend *fe,
					       u16 *signal_strength)
{
	struct mxl111sf_demod_state *state = fe->demodulator_priv;
	enum fe_modulation modulation;
	int ret;
	u16 snr;

	ret = mxl111sf_demod_calc_snr(state, &snr);
	if (ret < 0)
		return ret;
	ret = mxl1x1sf_demod_get_tps_modulation(state, &modulation);
	if (ret < 0)
		return ret;

	switch (modulation) {
	case QPSK:
		*signal_strength = (snr >= 1300) ?
			min(65535, snr * 44) : snr * 38;
		break;
	case QAM_16:
		*signal_strength = (snr >= 1500) ?
			min(65535, snr * 38) : snr * 33;
		break;
	case QAM_64:
		*signal_strength = (snr >= 2000) ?
			min(65535, snr * 29) : snr * 25;
		break;
	default:
		*signal_strength = 0;
		return -EINVAL;
	}

	return 0;
}