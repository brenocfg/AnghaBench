#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct stv {int receive_mode; int first_time_lock; int tscfgh; int demod_bits; int berscale; int last_berdenominator; int mod_cod; scalar_t__ regoff; scalar_t__ is_vcm; int /*<<< orphan*/  puncture_rate; scalar_t__ last_bernumerator; int /*<<< orphan*/  demod_lock_time; } ;
struct TYPE_16__ {TYPE_7__* stat; } ;
struct TYPE_14__ {TYPE_5__* stat; } ;
struct TYPE_12__ {TYPE_3__* stat; } ;
struct TYPE_10__ {TYPE_1__* stat; } ;
struct dtv_frontend_properties {TYPE_8__ pre_bit_count; TYPE_6__ pre_bit_error; TYPE_4__ cnr; TYPE_2__ strength; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct stv* demodulator_priv; } ;
typedef  enum receive_mode { ____Placeholder_receive_mode } receive_mode ;
typedef  enum fe_stv0910_mod_cod { ____Placeholder_fe_stv0910_mod_cod } fe_stv0910_mod_cod ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;
struct TYPE_15__ {void* scale; } ;
struct TYPE_13__ {void* scale; } ;
struct TYPE_11__ {void* scale; } ;
struct TYPE_9__ {void* scale; } ;

/* Variables and functions */
 int BER_SRC_S ; 
 int BER_SRC_S2 ; 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
 scalar_t__ RCVMODE_DVBS ; 
 scalar_t__ RCVMODE_DVBS2 ; 
 int RCVMODE_NONE ; 
 scalar_t__ RSTV0910_P2_DEMOD ; 
 scalar_t__ RSTV0910_P2_DMDMODCOD ; 
 scalar_t__ RSTV0910_P2_DMDSTATE ; 
 scalar_t__ RSTV0910_P2_DSTATUS ; 
 scalar_t__ RSTV0910_P2_ERRCTRL1 ; 
 scalar_t__ RSTV0910_P2_ERRCTRL2 ; 
 scalar_t__ RSTV0910_P2_FBERCPT4 ; 
 scalar_t__ RSTV0910_P2_PDELCTRL2 ; 
 scalar_t__ RSTV0910_P2_PDELSTATUS1 ; 
 scalar_t__ RSTV0910_P2_TSCFGH ; 
 scalar_t__ RSTV0910_P2_VSTATUSVIT ; 
 int /*<<< orphan*/  enable_puncture_rate (struct stv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_signal_parameters (struct stv*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  manage_matype_info (struct stv*) ; 
 int /*<<< orphan*/  read_ber (struct dvb_frontend*) ; 
 int /*<<< orphan*/  read_reg (struct stv*,scalar_t__,int*) ; 
 int /*<<< orphan*/  read_signal_strength (struct dvb_frontend*) ; 
 int /*<<< orphan*/  read_snr (struct dvb_frontend*) ; 
 int /*<<< orphan*/  set_vth (struct stv*) ; 
 int /*<<< orphan*/  set_vth_default (struct stv*) ; 
 int /*<<< orphan*/  tracking_optimization (struct stv*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  write_reg (struct stv*,scalar_t__,int) ; 

__attribute__((used)) static int read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	struct stv *state = fe->demodulator_priv;
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	u8 dmd_state = 0;
	u8 dstatus  = 0;
	enum receive_mode cur_receive_mode = RCVMODE_NONE;
	u32 feclock = 0;

	*status = 0;

	read_reg(state, RSTV0910_P2_DMDSTATE + state->regoff, &dmd_state);

	if (dmd_state & 0x40) {
		read_reg(state, RSTV0910_P2_DSTATUS + state->regoff, &dstatus);
		if (dstatus & 0x08)
			cur_receive_mode = (dmd_state & 0x20) ?
				RCVMODE_DVBS : RCVMODE_DVBS2;
	}
	if (cur_receive_mode == RCVMODE_NONE) {
		set_vth(state);

		/* reset signal statistics */
		p->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		p->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		p->pre_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

		return 0;
	}

	*status |= (FE_HAS_SIGNAL
		| FE_HAS_CARRIER
		| FE_HAS_VITERBI
		| FE_HAS_SYNC);

	if (state->receive_mode == RCVMODE_NONE) {
		state->receive_mode = cur_receive_mode;
		state->demod_lock_time = jiffies;
		state->first_time_lock = 1;

		get_signal_parameters(state);
		tracking_optimization(state);

		write_reg(state, RSTV0910_P2_TSCFGH + state->regoff,
			  state->tscfgh);
		usleep_range(3000, 4000);
		write_reg(state, RSTV0910_P2_TSCFGH + state->regoff,
			  state->tscfgh | 0x01);
		write_reg(state, RSTV0910_P2_TSCFGH + state->regoff,
			  state->tscfgh);
	}
	if (dmd_state & 0x40) {
		if (state->receive_mode == RCVMODE_DVBS2) {
			u8 pdelstatus;

			read_reg(state,
				 RSTV0910_P2_PDELSTATUS1 + state->regoff,
				 &pdelstatus);
			feclock = (pdelstatus & 0x02) != 0;
		} else {
			u8 vstatus;

			read_reg(state,
				 RSTV0910_P2_VSTATUSVIT + state->regoff,
				 &vstatus);
			feclock = (vstatus & 0x08) != 0;
		}
	}

	if (feclock) {
		*status |= FE_HAS_LOCK;

		if (state->first_time_lock) {
			u8 tmp;

			state->first_time_lock = 0;

			manage_matype_info(state);

			if (state->receive_mode == RCVMODE_DVBS2) {
				/*
				 * FSTV0910_P2_MANUALSX_ROLLOFF,
				 * FSTV0910_P2_MANUALS2_ROLLOFF = 0
				 */
				state->demod_bits &= ~0x84;
				write_reg(state,
					  RSTV0910_P2_DEMOD + state->regoff,
					  state->demod_bits);
				read_reg(state,
					 RSTV0910_P2_PDELCTRL2 + state->regoff,
					 &tmp);
				/* reset DVBS2 packet delinator error counter */
				tmp |= 0x40;
				write_reg(state,
					  RSTV0910_P2_PDELCTRL2 + state->regoff,
					  tmp);
				/* reset DVBS2 packet delinator error counter */
				tmp &= ~0x40;
				write_reg(state,
					  RSTV0910_P2_PDELCTRL2 + state->regoff,
					  tmp);

				state->berscale = 2;
				state->last_bernumerator = 0;
				state->last_berdenominator = 1;
				/* force to PRE BCH Rate */
				write_reg(state,
					  RSTV0910_P2_ERRCTRL1 + state->regoff,
					  BER_SRC_S2 | state->berscale);
			} else {
				state->berscale = 2;
				state->last_bernumerator = 0;
				state->last_berdenominator = 1;
				/* force to PRE RS Rate */
				write_reg(state,
					  RSTV0910_P2_ERRCTRL1 + state->regoff,
					  BER_SRC_S | state->berscale);
			}
			/* Reset the Total packet counter */
			write_reg(state,
				  RSTV0910_P2_FBERCPT4 + state->regoff, 0x00);
			/*
			 * Reset the packet Error counter2 (and Set it to
			 * infinite error count mode)
			 */
			write_reg(state,
				  RSTV0910_P2_ERRCTRL2 + state->regoff, 0xc1);

			set_vth_default(state);
			if (state->receive_mode == RCVMODE_DVBS)
				enable_puncture_rate(state,
						     state->puncture_rate);
		}

		/* Use highest signaled ModCod for quality */
		if (state->is_vcm) {
			u8 tmp;
			enum fe_stv0910_mod_cod mod_cod;

			read_reg(state, RSTV0910_P2_DMDMODCOD + state->regoff,
				 &tmp);
			mod_cod = (enum fe_stv0910_mod_cod)((tmp & 0x7c) >> 2);

			if (mod_cod > state->mod_cod)
				state->mod_cod = mod_cod;
		}
	}

	/* read signal statistics */

	/* read signal strength */
	read_signal_strength(fe);

	/* read carrier/noise on FE_HAS_CARRIER */
	if (*status & FE_HAS_CARRIER)
		read_snr(fe);
	else
		p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	/* read ber */
	if (*status & FE_HAS_VITERBI) {
		read_ber(fe);
	} else {
		p->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		p->pre_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	}

	return 0;
}