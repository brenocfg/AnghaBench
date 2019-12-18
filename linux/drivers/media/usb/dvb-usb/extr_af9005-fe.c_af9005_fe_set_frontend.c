#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_3__ {int (* set_params ) (struct dvb_frontend*) ;int /*<<< orphan*/ * release; } ;
struct TYPE_4__ {TYPE_1__ tuner_ops; } ;
struct dtv_frontend_properties {int /*<<< orphan*/  bandwidth_hz; int /*<<< orphan*/  frequency; } ;
struct dvb_frontend {TYPE_2__ ops; struct af9005_fe_state* demodulator_priv; struct dtv_frontend_properties dtv_property_cache; } ;
struct af9005_fe_state {int original_fcw; int strong; int /*<<< orphan*/  next_status_check; scalar_t__ abort_count; scalar_t__ post_vit_error_count; scalar_t__ ber; scalar_t__ pre_vit_bit_count; scalar_t__ pre_vit_error_count; int /*<<< orphan*/  d; scalar_t__ original_if_unplug_th; int /*<<< orphan*/  original_aci1_if_top; int /*<<< orphan*/  original_aci0_if_top; int /*<<< orphan*/  original_if_top; int /*<<< orphan*/  original_rf_top; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  XD_MP2IF_MISC ; 
 int af9005_fe_program_cfoe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int af9005_fe_select_bw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int af9005_led_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  af9005_reset_post_viterbi (struct dvb_frontend*) ; 
 int /*<<< orphan*/  af9005_reset_pre_viterbi (struct dvb_frontend*) ; 
 int af9005_write_ofdm_register (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int af9005_write_register_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int af9005_write_tuner_registers (int /*<<< orphan*/ ,int,scalar_t__*,int) ; 
 int af9005_write_word_agc (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deb_info (char*,...) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  jiffies ; 
 int reg_api_retrain_request_pos ; 
 int stub1 (struct dvb_frontend*) ; 
 int xd_p_reg_aagc_if_top_numerator_7_0 ; 
 int xd_p_reg_aagc_if_top_numerator_9_8 ; 
 int xd_p_reg_aagc_rf_top_numerator_7_0 ; 
 int xd_p_reg_aagc_rf_top_numerator_9_8 ; 
 int /*<<< orphan*/  xd_p_reg_api_retrain_request ; 
 int xd_p_reg_unplug_th ; 

__attribute__((used)) static int af9005_fe_set_frontend(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *fep = &fe->dtv_property_cache;
	struct af9005_fe_state *state = fe->demodulator_priv;
	int ret;
	u8 temp, temp0, temp1, temp2;

	deb_info("af9005_fe_set_frontend freq %d bw %d\n", fep->frequency,
		 fep->bandwidth_hz);
	if (fe->ops.tuner_ops.release == NULL) {
		err("Tuner not attached");
		return -ENODEV;
	}

	deb_info("turn off led\n");
	/* not in the log */
	ret = af9005_led_control(state->d, 0);
	if (ret)
		return ret;
	/* not sure about the bits */
	ret = af9005_write_register_bits(state->d, XD_MP2IF_MISC, 2, 1, 0);
	if (ret)
		return ret;

	/* set FCW to default value */
	deb_info("set FCW to default value\n");
	temp0 = (u8) (state->original_fcw & 0x000000ff);
	temp1 = (u8) ((state->original_fcw & 0x0000ff00) >> 8);
	temp2 = (u8) ((state->original_fcw & 0x00ff0000) >> 16);
	ret = af9005_write_ofdm_register(state->d, 0xae1a, temp0);
	if (ret)
		return ret;
	ret = af9005_write_ofdm_register(state->d, 0xae19, temp1);
	if (ret)
		return ret;
	ret = af9005_write_ofdm_register(state->d, 0xae18, temp2);
	if (ret)
		return ret;

	/* restore original TOPs */
	deb_info("restore original TOPs\n");
	ret =
	    af9005_write_word_agc(state->d,
				  xd_p_reg_aagc_rf_top_numerator_9_8,
				  xd_p_reg_aagc_rf_top_numerator_7_0, 0, 2,
				  state->original_rf_top);
	if (ret)
		return ret;
	ret =
	    af9005_write_word_agc(state->d,
				  xd_p_reg_aagc_if_top_numerator_9_8,
				  xd_p_reg_aagc_if_top_numerator_7_0, 0, 2,
				  state->original_if_top);
	if (ret)
		return ret;
	ret =
	    af9005_write_word_agc(state->d, 0xA60E, 0xA60A, 4, 2,
				  state->original_aci0_if_top);
	if (ret)
		return ret;
	ret =
	    af9005_write_word_agc(state->d, 0xA60E, 0xA60B, 6, 2,
				  state->original_aci1_if_top);
	if (ret)
		return ret;

	/* select bandwidth */
	deb_info("select bandwidth");
	ret = af9005_fe_select_bw(state->d, fep->bandwidth_hz);
	if (ret)
		return ret;
	ret = af9005_fe_program_cfoe(state->d, fep->bandwidth_hz);
	if (ret)
		return ret;

	/* clear easy mode flag */
	deb_info("clear easy mode flag\n");
	ret = af9005_write_ofdm_register(state->d, 0xaefd, 0);
	if (ret)
		return ret;

	/* set unplug threshold to original value */
	deb_info("set unplug threshold to original value\n");
	ret =
	    af9005_write_ofdm_register(state->d, xd_p_reg_unplug_th,
				       state->original_if_unplug_th);
	if (ret)
		return ret;
	/* set tuner */
	deb_info("set tuner\n");
	ret = fe->ops.tuner_ops.set_params(fe);
	if (ret)
		return ret;

	/* trigger ofsm */
	deb_info("trigger ofsm\n");
	temp = 0;
	ret = af9005_write_tuner_registers(state->d, 0xffff, &temp, 1);
	if (ret)
		return ret;

	/* clear retrain and freeze flag */
	deb_info("clear retrain and freeze flag\n");
	ret =
	    af9005_write_register_bits(state->d,
				       xd_p_reg_api_retrain_request,
				       reg_api_retrain_request_pos, 2, 0);
	if (ret)
		return ret;

	/* reset pre viterbi and post viterbi registers and statistics */
	af9005_reset_pre_viterbi(fe);
	af9005_reset_post_viterbi(fe);
	state->pre_vit_error_count = 0;
	state->pre_vit_bit_count = 0;
	state->ber = 0;
	state->post_vit_error_count = 0;
	/* state->unc = 0; commented out since it should be ever increasing */
	state->abort_count = 0;

	state->next_status_check = jiffies;
	state->strong = -1;

	return 0;
}