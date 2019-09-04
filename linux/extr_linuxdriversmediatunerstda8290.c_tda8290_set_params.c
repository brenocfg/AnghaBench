#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* agcf ) (struct dvb_frontend*) ;scalar_t__ config; } ;
struct tda8290_priv {int tda8290_easy_mode; int /*<<< orphan*/  i2c_props; TYPE_1__ cfg; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* set_analog_params ) (struct dvb_frontend*,struct analog_parameters*) ;} ;
struct TYPE_10__ {TYPE_2__ analog_ops; TYPE_3__ tuner_ops; } ;
struct dvb_frontend {TYPE_4__ ops; struct tda8290_priv* analog_demod_priv; } ;
struct analog_parameters {scalar_t__ mode; } ;
struct TYPE_11__ {unsigned char* seq; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_5__*) ; 
 scalar_t__ V4L2_TUNER_RADIO ; 
 scalar_t__ deemphasis_50 ; 
 TYPE_5__* fm_mode ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  set_audio (struct dvb_frontend*,struct analog_parameters*) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,struct analog_parameters*) ; 
 int /*<<< orphan*/  stub3 (struct dvb_frontend*) ; 
 int /*<<< orphan*/  stub4 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  tuner_dbg (char*,...) ; 
 int /*<<< orphan*/  tuner_i2c_xfer_send (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  tuner_i2c_xfer_send_recv (int /*<<< orphan*/ *,unsigned char*,int,unsigned char*,int) ; 

__attribute__((used)) static void tda8290_set_params(struct dvb_frontend *fe,
			       struct analog_parameters *params)
{
	struct tda8290_priv *priv = fe->analog_demod_priv;

	static unsigned char soft_reset[]  = { 0x00, 0x00 };
	unsigned char easy_mode[]   = { 0x01, priv->tda8290_easy_mode };
	static unsigned char expert_mode[] = { 0x01, 0x80 };
	static unsigned char agc_out_on[]  = { 0x02, 0x00 };
	static unsigned char gainset_off[] = { 0x28, 0x14 };
	static unsigned char if_agc_spd[]  = { 0x0f, 0x88 };
	static unsigned char adc_head_6[]  = { 0x05, 0x04 };
	static unsigned char adc_head_9[]  = { 0x05, 0x02 };
	static unsigned char adc_head_12[] = { 0x05, 0x01 };
	static unsigned char pll_bw_nom[]  = { 0x0d, 0x47 };
	static unsigned char pll_bw_low[]  = { 0x0d, 0x27 };
	static unsigned char gainset_2[]   = { 0x28, 0x64 };
	static unsigned char agc_rst_on[]  = { 0x0e, 0x0b };
	static unsigned char agc_rst_off[] = { 0x0e, 0x09 };
	static unsigned char if_agc_set[]  = { 0x0f, 0x81 };
	static unsigned char addr_adc_sat  = 0x1a;
	static unsigned char addr_agc_stat = 0x1d;
	static unsigned char addr_pll_stat = 0x1b;
	static unsigned char adc_sat = 0, agc_stat = 0,
		      pll_stat;
	int i;

	set_audio(fe, params);

	if (priv->cfg.config)
		tuner_dbg("tda827xa config is 0x%02x\n", priv->cfg.config);
	tuner_i2c_xfer_send(&priv->i2c_props, easy_mode, 2);
	tuner_i2c_xfer_send(&priv->i2c_props, agc_out_on, 2);
	tuner_i2c_xfer_send(&priv->i2c_props, soft_reset, 2);
	msleep(1);

	if (params->mode == V4L2_TUNER_RADIO) {
		unsigned char deemphasis[]  = { 0x13, 1 };

		/* FIXME: allow using a different deemphasis */

		if (deemphasis_50)
			deemphasis[1] = 2;

		for (i = 0; i < ARRAY_SIZE(fm_mode); i++)
			tuner_i2c_xfer_send(&priv->i2c_props, fm_mode[i].seq, 2);

		tuner_i2c_xfer_send(&priv->i2c_props, deemphasis, 2);
	} else {
		expert_mode[1] = priv->tda8290_easy_mode + 0x80;
		tuner_i2c_xfer_send(&priv->i2c_props, expert_mode, 2);
		tuner_i2c_xfer_send(&priv->i2c_props, gainset_off, 2);
		tuner_i2c_xfer_send(&priv->i2c_props, if_agc_spd, 2);
		if (priv->tda8290_easy_mode & 0x60)
			tuner_i2c_xfer_send(&priv->i2c_props, adc_head_9, 2);
		else
			tuner_i2c_xfer_send(&priv->i2c_props, adc_head_6, 2);
		tuner_i2c_xfer_send(&priv->i2c_props, pll_bw_nom, 2);
	}


	if (fe->ops.analog_ops.i2c_gate_ctrl)
		fe->ops.analog_ops.i2c_gate_ctrl(fe, 1);

	if (fe->ops.tuner_ops.set_analog_params)
		fe->ops.tuner_ops.set_analog_params(fe, params);

	for (i = 0; i < 3; i++) {
		tuner_i2c_xfer_send_recv(&priv->i2c_props,
					 &addr_pll_stat, 1, &pll_stat, 1);
		if (pll_stat & 0x80) {
			tuner_i2c_xfer_send_recv(&priv->i2c_props,
						 &addr_adc_sat, 1,
						 &adc_sat, 1);
			tuner_i2c_xfer_send_recv(&priv->i2c_props,
						 &addr_agc_stat, 1,
						 &agc_stat, 1);
			tuner_dbg("tda8290 is locked, AGC: %d\n", agc_stat);
			break;
		} else {
			tuner_dbg("tda8290 not locked, no signal?\n");
			msleep(100);
		}
	}
	/* adjust headroom resp. gain */
	if ((agc_stat > 115) || (!(pll_stat & 0x80) && (adc_sat < 20))) {
		tuner_dbg("adjust gain, step 1. Agc: %d, ADC stat: %d, lock: %d\n",
			   agc_stat, adc_sat, pll_stat & 0x80);
		tuner_i2c_xfer_send(&priv->i2c_props, gainset_2, 2);
		msleep(100);
		tuner_i2c_xfer_send_recv(&priv->i2c_props,
					 &addr_agc_stat, 1, &agc_stat, 1);
		tuner_i2c_xfer_send_recv(&priv->i2c_props,
					 &addr_pll_stat, 1, &pll_stat, 1);
		if ((agc_stat > 115) || !(pll_stat & 0x80)) {
			tuner_dbg("adjust gain, step 2. Agc: %d, lock: %d\n",
				   agc_stat, pll_stat & 0x80);
			if (priv->cfg.agcf)
				priv->cfg.agcf(fe);
			msleep(100);
			tuner_i2c_xfer_send_recv(&priv->i2c_props,
						 &addr_agc_stat, 1,
						 &agc_stat, 1);
			tuner_i2c_xfer_send_recv(&priv->i2c_props,
						 &addr_pll_stat, 1,
						 &pll_stat, 1);
			if((agc_stat > 115) || !(pll_stat & 0x80)) {
				tuner_dbg("adjust gain, step 3. Agc: %d\n", agc_stat);
				tuner_i2c_xfer_send(&priv->i2c_props, adc_head_12, 2);
				tuner_i2c_xfer_send(&priv->i2c_props, pll_bw_low, 2);
				msleep(100);
			}
		}
	}

	/* l/ l' deadlock? */
	if(priv->tda8290_easy_mode & 0x60) {
		tuner_i2c_xfer_send_recv(&priv->i2c_props,
					 &addr_adc_sat, 1,
					 &adc_sat, 1);
		tuner_i2c_xfer_send_recv(&priv->i2c_props,
					 &addr_pll_stat, 1,
					 &pll_stat, 1);
		if ((adc_sat > 20) || !(pll_stat & 0x80)) {
			tuner_dbg("trying to resolve SECAM L deadlock\n");
			tuner_i2c_xfer_send(&priv->i2c_props, agc_rst_on, 2);
			msleep(40);
			tuner_i2c_xfer_send(&priv->i2c_props, agc_rst_off, 2);
		}
	}

	if (fe->ops.analog_ops.i2c_gate_ctrl)
		fe->ops.analog_ops.i2c_gate_ctrl(fe, 0);
	tuner_i2c_xfer_send(&priv->i2c_props, if_agc_set, 2);
}