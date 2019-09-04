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
struct stv0900_state {int demod; struct stv0900_internal* internal; } ;
struct stv0900_internal {scalar_t__* srch_algo; TYPE_1__* result; int /*<<< orphan*/  mclk; } ;
struct dvb_frontend {struct stv0900_state* demodulator_priv; } ;
typedef  int s32 ;
typedef  enum fe_stv0900_signal_type { ____Placeholder_fe_stv0900_signal_type } fe_stv0900_signal_type ;
typedef  enum fe_stv0900_demod_num { ____Placeholder_fe_stv0900_demod_num } fe_stv0900_demod_num ;
struct TYPE_2__ {void* locked; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFR1 ; 
 int /*<<< orphan*/  CFR2 ; 
 int /*<<< orphan*/  CFRINIT0 ; 
 int /*<<< orphan*/  CFRINIT1 ; 
 int /*<<< orphan*/  CFR_AUTOSCAN ; 
 int /*<<< orphan*/  DMDISTATE ; 
 void* FALSE ; 
 int /*<<< orphan*/  HEADER_MODE ; 
 int /*<<< orphan*/  SPECINV_CONTROL ; 
 scalar_t__ STV0900_BLIND_SEARCH ; 
 scalar_t__ STV0900_DVBS_FOUND ; 
 int /*<<< orphan*/  STV0900_IQ_FORCE_NORMAL ; 
 int /*<<< orphan*/  STV0900_IQ_FORCE_SWAPPED ; 
 int STV0900_NODATA ; 
 int /*<<< orphan*/  STV0900_WARM_START ; 
 scalar_t__ TRUE ; 
 scalar_t__ stv0900_get_bits (struct stv0900_internal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv0900_get_lock_timeout (int*,int*,int,int /*<<< orphan*/ ) ; 
 int stv0900_get_signal_params (struct dvb_frontend*) ; 
 int stv0900_get_symbol_rate (struct stv0900_internal*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stv0900_get_timing_offst (struct stv0900_internal*,int,int) ; 
 int stv0900_read_reg (struct stv0900_internal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv0900_set_symbol_rate (struct stv0900_internal*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stv0900_track_optimization (struct dvb_frontend*) ; 
 scalar_t__ stv0900_wait_for_lock (struct stv0900_internal*,int,int,int) ; 
 int /*<<< orphan*/  stv0900_write_bits (struct stv0900_internal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv0900_write_reg (struct stv0900_internal*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum
fe_stv0900_signal_type stv0900_dvbs1_acq_workaround(struct dvb_frontend *fe)
{
	struct stv0900_state *state = fe->demodulator_priv;
	struct stv0900_internal *intp = state->internal;
	enum fe_stv0900_demod_num demod = state->demod;
	enum fe_stv0900_signal_type signal_type = STV0900_NODATA;

	s32	srate,
		demod_timeout,
		fec_timeout,
		freq1,
		freq0;

	intp->result[demod].locked = FALSE;

	if (stv0900_get_bits(intp, HEADER_MODE) == STV0900_DVBS_FOUND) {
		srate = stv0900_get_symbol_rate(intp, intp->mclk, demod);
		srate += stv0900_get_timing_offst(intp, srate, demod);
		if (intp->srch_algo[demod] == STV0900_BLIND_SEARCH)
			stv0900_set_symbol_rate(intp, intp->mclk, srate, demod);

		stv0900_get_lock_timeout(&demod_timeout, &fec_timeout,
					srate, STV0900_WARM_START);
		freq1 = stv0900_read_reg(intp, CFR2);
		freq0 = stv0900_read_reg(intp, CFR1);
		stv0900_write_bits(intp, CFR_AUTOSCAN, 0);
		stv0900_write_bits(intp, SPECINV_CONTROL,
					STV0900_IQ_FORCE_SWAPPED);
		stv0900_write_reg(intp, DMDISTATE, 0x1c);
		stv0900_write_reg(intp, CFRINIT1, freq1);
		stv0900_write_reg(intp, CFRINIT0, freq0);
		stv0900_write_reg(intp, DMDISTATE, 0x18);
		if (stv0900_wait_for_lock(intp, demod,
				demod_timeout, fec_timeout) == TRUE) {
			intp->result[demod].locked = TRUE;
			signal_type = stv0900_get_signal_params(fe);
			stv0900_track_optimization(fe);
		} else {
			stv0900_write_bits(intp, SPECINV_CONTROL,
					STV0900_IQ_FORCE_NORMAL);
			stv0900_write_reg(intp, DMDISTATE, 0x1c);
			stv0900_write_reg(intp, CFRINIT1, freq1);
			stv0900_write_reg(intp, CFRINIT0, freq0);
			stv0900_write_reg(intp, DMDISTATE, 0x18);
			if (stv0900_wait_for_lock(intp, demod,
					demod_timeout, fec_timeout) == TRUE) {
				intp->result[demod].locked = TRUE;
				signal_type = stv0900_get_signal_params(fe);
				stv0900_track_optimization(fe);
			}

		}

	} else
		intp->result[demod].locked = FALSE;

	return signal_type;
}