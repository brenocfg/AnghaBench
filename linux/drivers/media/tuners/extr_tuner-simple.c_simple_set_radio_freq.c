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
typedef  int u8 ;
typedef  int u16 ;
struct v4l2_priv_tun_config {int* priv; int /*<<< orphan*/  tuner; } ;
struct tunertype {int count; struct tuner_params* params; } ;
struct TYPE_4__ {int /*<<< orphan*/  adap; } ;
struct tuner_simple_priv {int last_div; int type; TYPE_2__ i2c_props; struct tunertype* tun; } ;
struct tuner_params {scalar_t__ type; int radio_if; scalar_t__ fm_gain_normal; scalar_t__ port1_set_for_fm_mono; scalar_t__ intercarrier_mode; int /*<<< orphan*/  port2_fm_high_sensitivity; scalar_t__ port2_active; int /*<<< orphan*/  port1_fm_high_sensitivity; scalar_t__ port1_active; scalar_t__ has_tda9887; scalar_t__ cb_first_if_lower_freq; TYPE_1__* ranges; } ;
struct dvb_frontend {struct tuner_simple_priv* tuner_priv; } ;
struct analog_parameters {unsigned int frequency; scalar_t__ audmode; } ;
struct TYPE_3__ {int config; } ;

/* Variables and functions */
 int TDA9887_GAIN_NORMAL ; 
 int TDA9887_INTERCARRIER ; 
 int TDA9887_PORT1_ACTIVE ; 
 int TDA9887_PORT2_ACTIVE ; 
 int TDA9887_RIF_41_3 ; 
 scalar_t__ TUNER_PARAM_TYPE_RADIO ; 
#define  TUNER_PHILIPS_FM1216ME_MK3 128 
 int TUNER_RATIO_MASK ; 
 int TUNER_RATIO_SELECT_50 ; 
 int /*<<< orphan*/  TUNER_SET_CONFIG ; 
 int /*<<< orphan*/  TUNER_TDA9887 ; 
 scalar_t__ V4L2_TUNER_MODE_MONO ; 
 int /*<<< orphan*/  i2c_clients_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_priv_tun_config*) ; 
 int /*<<< orphan*/  simple_radio_bandswitch (struct dvb_frontend*,int*) ; 
 int /*<<< orphan*/  tuner_dbg (char*,int,int,int,int) ; 
 int tuner_i2c_xfer_send (TYPE_2__*,int*,int) ; 
 int /*<<< orphan*/  tuner_warn (char*,int) ; 

__attribute__((used)) static int simple_set_radio_freq(struct dvb_frontend *fe,
				 struct analog_parameters *params)
{
	struct tunertype *tun;
	struct tuner_simple_priv *priv = fe->tuner_priv;
	u8 buffer[4];
	u16 div;
	int rc, j;
	struct tuner_params *t_params;
	unsigned int freq = params->frequency;
	bool mono = params->audmode == V4L2_TUNER_MODE_MONO;

	tun = priv->tun;

	for (j = tun->count-1; j > 0; j--)
		if (tun->params[j].type == TUNER_PARAM_TYPE_RADIO)
			break;
	/* default t_params (j=0) will be used if desired type wasn't found */
	t_params = &tun->params[j];

	/* Select Radio 1st IF used */
	switch (t_params->radio_if) {
	case 0: /* 10.7 MHz */
		freq += (unsigned int)(10.7*16000);
		break;
	case 1: /* 33.3 MHz */
		freq += (unsigned int)(33.3*16000);
		break;
	case 2: /* 41.3 MHz */
		freq += (unsigned int)(41.3*16000);
		break;
	default:
		tuner_warn("Unsupported radio_if value %d\n",
			   t_params->radio_if);
		return 0;
	}

	buffer[2] = (t_params->ranges[0].config & ~TUNER_RATIO_MASK) |
		    TUNER_RATIO_SELECT_50; /* 50 kHz step */

	/* Bandswitch byte */
	simple_radio_bandswitch(fe, &buffer[0]);

	/* Convert from 1/16 kHz V4L steps to 1/20 MHz (=50 kHz) PLL steps
	   freq * (1 Mhz / 16000 V4L steps) * (20 PLL steps / 1 MHz) =
	   freq * (1/800) */
	div = (freq + 400) / 800;

	if (t_params->cb_first_if_lower_freq && div < priv->last_div) {
		buffer[0] = buffer[2];
		buffer[1] = buffer[3];
		buffer[2] = (div>>8) & 0x7f;
		buffer[3] = div      & 0xff;
	} else {
		buffer[0] = (div>>8) & 0x7f;
		buffer[1] = div      & 0xff;
	}

	tuner_dbg("radio 0x%02x 0x%02x 0x%02x 0x%02x\n",
	       buffer[0], buffer[1], buffer[2], buffer[3]);
	priv->last_div = div;

	if (t_params->has_tda9887) {
		int config = 0;
		struct v4l2_priv_tun_config tda9887_cfg;

		tda9887_cfg.tuner = TUNER_TDA9887;
		tda9887_cfg.priv = &config;

		if (t_params->port1_active &&
		    !t_params->port1_fm_high_sensitivity)
			config |= TDA9887_PORT1_ACTIVE;
		if (t_params->port2_active &&
		    !t_params->port2_fm_high_sensitivity)
			config |= TDA9887_PORT2_ACTIVE;
		if (t_params->intercarrier_mode)
			config |= TDA9887_INTERCARRIER;
		if (t_params->port1_set_for_fm_mono && mono)
			config &= ~TDA9887_PORT1_ACTIVE;
		if (t_params->fm_gain_normal)
			config |= TDA9887_GAIN_NORMAL;
		if (t_params->radio_if == 2)
			config |= TDA9887_RIF_41_3;
		i2c_clients_command(priv->i2c_props.adap, TUNER_SET_CONFIG,
				    &tda9887_cfg);
	}
	rc = tuner_i2c_xfer_send(&priv->i2c_props, buffer, 4);
	if (4 != rc)
		tuner_warn("i2c i/o error: rc == %d (should be 4)\n", rc);

	/* Write AUX byte */
	switch (priv->type) {
	case TUNER_PHILIPS_FM1216ME_MK3:
		buffer[2] = 0x98;
		buffer[3] = 0x20; /* set TOP AGC */
		rc = tuner_i2c_xfer_send(&priv->i2c_props, buffer, 4);
		if (4 != rc)
			tuner_warn("i2c i/o error: rc == %d (should be 4)\n", rc);
		break;
	}

	return 0;
}