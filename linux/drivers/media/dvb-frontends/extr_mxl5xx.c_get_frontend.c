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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct mxl {int /*<<< orphan*/  i2cdev; TYPE_1__* base; int /*<<< orphan*/  demod; } ;
struct dvb_frontend {struct mxl* demodulator_priv; } ;
struct dtv_frontend_properties {int symbol_rate; int frequency; int delivery_system; int /*<<< orphan*/  rolloff; int /*<<< orphan*/  modulation; int /*<<< orphan*/  pilot; int /*<<< orphan*/  fec_inner; } ;
typedef  enum MXL_HYDRA_ROLLOFF_E { ____Placeholder_MXL_HYDRA_ROLLOFF_E } MXL_HYDRA_ROLLOFF_E ;
typedef  enum MXL_HYDRA_PILOTS_E { ____Placeholder_MXL_HYDRA_PILOTS_E } MXL_HYDRA_PILOTS_E ;
typedef  enum MXL_HYDRA_MODULATION_E { ____Placeholder_MXL_HYDRA_MODULATION_E } MXL_HYDRA_MODULATION_E ;
struct TYPE_2__ {int /*<<< orphan*/  status_lock; } ;

/* Variables and functions */
 size_t DMD_DVBS2_PILOT_ON_OFF_ADDR ; 
 size_t DMD_FEC_CODE_RATE_ADDR ; 
 size_t DMD_MODULATION_SCHEME_ADDR ; 
 size_t DMD_SPECTRUM_ROLL_OFF_ADDR ; 
 size_t DMD_STANDARD_ADDR ; 
 size_t DMD_SYMBOL_RATE_ADDR ; 
 int EINVAL ; 
 int /*<<< orphan*/  HYDRA_DEMOD_STATUS_LOCK (struct mxl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HYDRA_DEMOD_STATUS_UNLOCK (struct mxl*,int /*<<< orphan*/ ) ; 
 scalar_t__ HYDRA_DMD_STANDARD_ADDR_OFFSET ; 
 scalar_t__ HYDRA_DMD_STATUS_CENTER_FREQ_IN_KHZ_ADDR ; 
 scalar_t__ HYDRA_DMD_STATUS_OFFSET (int /*<<< orphan*/ ) ; 
 int MXL_DEMOD_CHAN_PARAMS_BUFF_SIZE ; 
#define  MXL_HYDRA_MOD_8PSK 137 
#define  MXL_HYDRA_MOD_QPSK 136 
#define  MXL_HYDRA_PILOTS_OFF 135 
#define  MXL_HYDRA_PILOTS_ON 134 
#define  MXL_HYDRA_ROLLOFF_0_20 133 
#define  MXL_HYDRA_ROLLOFF_0_25 132 
#define  MXL_HYDRA_ROLLOFF_0_35 131 
 int /*<<< orphan*/  PILOT_OFF ; 
 int /*<<< orphan*/  PILOT_ON ; 
 int /*<<< orphan*/  PSK_8 ; 
 int /*<<< orphan*/  QPSK ; 
 int /*<<< orphan*/  ROLLOFF_20 ; 
 int /*<<< orphan*/  ROLLOFF_25 ; 
 int /*<<< orphan*/  ROLLOFF_35 ; 
#define  SYS_DSS 130 
#define  SYS_DVBS 129 
#define  SYS_DVBS2 128 
 int /*<<< orphan*/  conv_fec (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_register_block (struct mxl*,scalar_t__,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_frontend(struct dvb_frontend *fe,
			struct dtv_frontend_properties *p)
{
	struct mxl *state = fe->demodulator_priv;
	u32 reg_data[MXL_DEMOD_CHAN_PARAMS_BUFF_SIZE];
	u32 freq;

	mutex_lock(&state->base->status_lock);
	HYDRA_DEMOD_STATUS_LOCK(state, state->demod);
	read_register_block(state,
		(HYDRA_DMD_STANDARD_ADDR_OFFSET +
		HYDRA_DMD_STATUS_OFFSET(state->demod)),
		(MXL_DEMOD_CHAN_PARAMS_BUFF_SIZE * 4), /* 25 * 4 bytes */
		(u8 *) &reg_data[0]);
	/* read demod channel parameters */
	read_register_block(state,
		(HYDRA_DMD_STATUS_CENTER_FREQ_IN_KHZ_ADDR +
		HYDRA_DMD_STATUS_OFFSET(state->demod)),
		(4), /* 4 bytes */
		(u8 *) &freq);
	HYDRA_DEMOD_STATUS_UNLOCK(state, state->demod);
	mutex_unlock(&state->base->status_lock);

	dev_dbg(state->i2cdev, "freq=%u delsys=%u srate=%u\n",
		freq * 1000, reg_data[DMD_STANDARD_ADDR],
		reg_data[DMD_SYMBOL_RATE_ADDR]);
	p->symbol_rate = reg_data[DMD_SYMBOL_RATE_ADDR];
	p->frequency = freq;
	/*
	 * p->delivery_system =
	 *	(MXL_HYDRA_BCAST_STD_E) regData[DMD_STANDARD_ADDR];
	 * p->inversion =
	 *	(MXL_HYDRA_SPECTRUM_E) regData[DMD_SPECTRUM_INVERSION_ADDR];
	 * freqSearchRangeKHz =
	 *	(regData[DMD_FREQ_SEARCH_RANGE_IN_KHZ_ADDR]);
	 */

	p->fec_inner = conv_fec(reg_data[DMD_FEC_CODE_RATE_ADDR]);
	switch (p->delivery_system) {
	case SYS_DSS:
		break;
	case SYS_DVBS2:
		switch ((enum MXL_HYDRA_PILOTS_E)
			reg_data[DMD_DVBS2_PILOT_ON_OFF_ADDR]) {
		case MXL_HYDRA_PILOTS_OFF:
			p->pilot = PILOT_OFF;
			break;
		case MXL_HYDRA_PILOTS_ON:
			p->pilot = PILOT_ON;
			break;
		default:
			break;
		}
		/* Fall through */
	case SYS_DVBS:
		switch ((enum MXL_HYDRA_MODULATION_E)
			reg_data[DMD_MODULATION_SCHEME_ADDR]) {
		case MXL_HYDRA_MOD_QPSK:
			p->modulation = QPSK;
			break;
		case MXL_HYDRA_MOD_8PSK:
			p->modulation = PSK_8;
			break;
		default:
			break;
		}
		switch ((enum MXL_HYDRA_ROLLOFF_E)
			reg_data[DMD_SPECTRUM_ROLL_OFF_ADDR]) {
		case MXL_HYDRA_ROLLOFF_0_20:
			p->rolloff = ROLLOFF_20;
			break;
		case MXL_HYDRA_ROLLOFF_0_35:
			p->rolloff = ROLLOFF_35;
			break;
		case MXL_HYDRA_ROLLOFF_0_25:
			p->rolloff = ROLLOFF_25;
			break;
		default:
			break;
		}
		break;
	default:
		return -EINVAL;
	}
	return 0;
}