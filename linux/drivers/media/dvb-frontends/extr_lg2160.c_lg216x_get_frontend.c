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
struct lg216x_state {int last_reset; TYPE_1__* cfg; int /*<<< orphan*/  parade_id; int /*<<< orphan*/  fic_ver; int /*<<< orphan*/  current_frequency; } ;
struct dvb_frontend {struct lg216x_state* demodulator_priv; } ;
struct dtv_frontend_properties {int atscmh_crc_err; int atscmh_rs_err; int /*<<< orphan*/  atscmh_fic_err; int /*<<< orphan*/  atscmh_sccc_code_mode_d; int /*<<< orphan*/  atscmh_sccc_code_mode_c; int /*<<< orphan*/  atscmh_sccc_code_mode_b; int /*<<< orphan*/  atscmh_sccc_code_mode_a; int /*<<< orphan*/  atscmh_sccc_block_mode; int /*<<< orphan*/  atscmh_rs_code_mode_sec; int /*<<< orphan*/  atscmh_rs_code_mode_pri; int /*<<< orphan*/  atscmh_rs_frame_ensemble; int /*<<< orphan*/  atscmh_rs_frame_mode; int /*<<< orphan*/  atscmh_prc; int /*<<< orphan*/  atscmh_sgn; int /*<<< orphan*/  atscmh_tnog; int /*<<< orphan*/  atscmh_nog; int /*<<< orphan*/  atscmh_parade_id; int /*<<< orphan*/  atscmh_fic_ver; int /*<<< orphan*/  delivery_system; int /*<<< orphan*/  frequency; int /*<<< orphan*/  modulation; } ;
typedef  enum atscmh_sccc_code_mode { ____Placeholder_atscmh_sccc_code_mode } atscmh_sccc_code_mode ;
typedef  enum atscmh_sccc_block_mode { ____Placeholder_atscmh_sccc_block_mode } atscmh_sccc_block_mode ;
typedef  enum atscmh_rs_frame_mode { ____Placeholder_atscmh_rs_frame_mode } atscmh_rs_frame_mode ;
typedef  enum atscmh_rs_frame_ensemble { ____Placeholder_atscmh_rs_frame_ensemble } atscmh_rs_frame_ensemble ;
typedef  enum atscmh_rs_code_mode { ____Placeholder_atscmh_rs_code_mode } atscmh_rs_code_mode ;
struct TYPE_2__ {int lg_chip; } ;

/* Variables and functions */
#define  LG2160 129 
#define  LG2161 128 
 int /*<<< orphan*/  SYS_ATSCMH ; 
 int /*<<< orphan*/  VSB_8 ; 
 int /*<<< orphan*/  jiffies ; 
 int jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int lg2160_get_parade_id (struct lg216x_state*,int /*<<< orphan*/ *) ; 
 int lg216x_get_fic_version (struct lg216x_state*,int /*<<< orphan*/ *) ; 
 int lg216x_get_nog (struct lg216x_state*,int /*<<< orphan*/ *) ; 
 int lg216x_get_prc (struct lg216x_state*,int /*<<< orphan*/ *) ; 
 int lg216x_get_rs_code_mode (struct lg216x_state*,int*,int*) ; 
 int lg216x_get_rs_frame_ensemble (struct lg216x_state*,int*) ; 
 int lg216x_get_rs_frame_mode (struct lg216x_state*,int*) ; 
 int lg216x_get_sccc_block_mode (struct lg216x_state*,int*) ; 
 int lg216x_get_sccc_code_mode (struct lg216x_state*,int*,int*,int*,int*) ; 
 int lg216x_get_sgn (struct lg216x_state*,int /*<<< orphan*/ *) ; 
 int lg216x_get_tnog (struct lg216x_state*,int /*<<< orphan*/ *) ; 
 int lg216x_read_crc_err_count (struct lg216x_state*,int*) ; 
 int lg216x_read_fic_err_count (struct lg216x_state*,int /*<<< orphan*/ *) ; 
 int lg216x_read_rs_err_count (struct lg216x_state*,int*) ; 
 int lg216x_soft_reset (struct lg216x_state*) ; 
 int /*<<< orphan*/  lg_dbg (char*) ; 
 scalar_t__ lg_fail (int) ; 

__attribute__((used)) static int lg216x_get_frontend(struct dvb_frontend *fe,
			       struct dtv_frontend_properties *c)
{
	struct lg216x_state *state = fe->demodulator_priv;
	int ret;

	lg_dbg("\n");

	c->modulation = VSB_8;
	c->frequency = state->current_frequency;
	c->delivery_system = SYS_ATSCMH;

	ret = lg216x_get_fic_version(state,
				     &c->atscmh_fic_ver);
	if (lg_fail(ret))
		goto fail;
	if (state->fic_ver != c->atscmh_fic_ver) {
		state->fic_ver = c->atscmh_fic_ver;

#if 0
		ret = lg2160_get_parade_id(state,
				&c->atscmh_parade_id);
		if (lg_fail(ret))
			goto fail;
/* #else */
		c->atscmh_parade_id = state->parade_id;
#endif
		ret = lg216x_get_nog(state,
				     &c->atscmh_nog);
		if (lg_fail(ret))
			goto fail;
		ret = lg216x_get_tnog(state,
				      &c->atscmh_tnog);
		if (lg_fail(ret))
			goto fail;
		ret = lg216x_get_sgn(state,
				     &c->atscmh_sgn);
		if (lg_fail(ret))
			goto fail;
		ret = lg216x_get_prc(state,
				     &c->atscmh_prc);
		if (lg_fail(ret))
			goto fail;

		ret = lg216x_get_rs_frame_mode(state,
			(enum atscmh_rs_frame_mode *)
			&c->atscmh_rs_frame_mode);
		if (lg_fail(ret))
			goto fail;
		ret = lg216x_get_rs_frame_ensemble(state,
			(enum atscmh_rs_frame_ensemble *)
			&c->atscmh_rs_frame_ensemble);
		if (lg_fail(ret))
			goto fail;
		ret = lg216x_get_rs_code_mode(state,
			(enum atscmh_rs_code_mode *)
			&c->atscmh_rs_code_mode_pri,
			(enum atscmh_rs_code_mode *)
			&c->atscmh_rs_code_mode_sec);
		if (lg_fail(ret))
			goto fail;
		ret = lg216x_get_sccc_block_mode(state,
			(enum atscmh_sccc_block_mode *)
			&c->atscmh_sccc_block_mode);
		if (lg_fail(ret))
			goto fail;
		ret = lg216x_get_sccc_code_mode(state,
			(enum atscmh_sccc_code_mode *)
			&c->atscmh_sccc_code_mode_a,
			(enum atscmh_sccc_code_mode *)
			&c->atscmh_sccc_code_mode_b,
			(enum atscmh_sccc_code_mode *)
			&c->atscmh_sccc_code_mode_c,
			(enum atscmh_sccc_code_mode *)
			&c->atscmh_sccc_code_mode_d);
		if (lg_fail(ret))
			goto fail;
	}
#if 0
	ret = lg216x_read_fic_err_count(state,
				(u8 *)&c->atscmh_fic_err);
	if (lg_fail(ret))
		goto fail;
	ret = lg216x_read_crc_err_count(state,
				&c->atscmh_crc_err);
	if (lg_fail(ret))
		goto fail;
	ret = lg216x_read_rs_err_count(state,
				&c->atscmh_rs_err);
	if (lg_fail(ret))
		goto fail;

	switch (state->cfg->lg_chip) {
	case LG2160:
		if (((c->atscmh_rs_err >= 240) &&
		     (c->atscmh_crc_err >= 240)) &&
		    ((jiffies_to_msecs(jiffies) - state->last_reset) > 6000))
			ret = lg216x_soft_reset(state);
		break;
	case LG2161:
		/* no fix needed here (as far as we know) */
		ret = 0;
		break;
	}
	lg_fail(ret);
#endif
fail:
	return ret;
}