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
typedef  int u8 ;
typedef  int u16 ;
struct v4l2_priv_tun_config {int* priv; int /*<<< orphan*/  tuner; } ;
struct TYPE_2__ {int /*<<< orphan*/  adap; } ;
struct tuner_simple_priv {int last_div; TYPE_1__ i2c_props; } ;
struct tuner_params {int port1_active; int port1_invert_for_secam_lc; int port2_active; int port2_invert_for_secam_lc; scalar_t__ default_pll_gating_18; scalar_t__ default_top_high; scalar_t__ default_top_mid; scalar_t__ default_top_low; scalar_t__ default_top_secam_high; scalar_t__ default_top_secam_mid; scalar_t__ default_top_secam_low; scalar_t__ intercarrier_mode; scalar_t__ has_tda9887; scalar_t__ cb_first_if_lower_freq; } ;
struct dvb_frontend {struct tuner_simple_priv* tuner_priv; } ;
struct analog_parameters {int std; int frequency; } ;
typedef  enum param_type { ____Placeholder_param_type } param_type ;

/* Variables and functions */
 int TDA9887_GATING_18 ; 
 int TDA9887_INTERCARRIER ; 
 int TDA9887_PORT1_ACTIVE ; 
 int TDA9887_PORT2_ACTIVE ; 
 int TDA9887_TOP (scalar_t__) ; 
 int TUNER_PARAM_TYPE_NTSC ; 
 int TUNER_PARAM_TYPE_PAL ; 
 int TUNER_PARAM_TYPE_SECAM ; 
 int /*<<< orphan*/  TUNER_SET_CONFIG ; 
 int /*<<< orphan*/  TUNER_TDA9887 ; 
 int V4L2_STD_MN ; 
 int V4L2_STD_NTSC_M_JP ; 
 int V4L2_STD_SECAM_L ; 
 int V4L2_STD_SECAM_LC ; 
 int /*<<< orphan*/  i2c_clients_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_priv_tun_config*) ; 
 int offset ; 
 int simple_config_lookup (struct dvb_frontend*,struct tuner_params*,int*,int*,int*) ; 
 int /*<<< orphan*/  simple_post_tune (struct dvb_frontend*,int*,int,int,int) ; 
 int /*<<< orphan*/  simple_std_setup (struct dvb_frontend*,struct analog_parameters*,int*,int*) ; 
 struct tuner_params* simple_tuner_params (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  tuner_dbg (char*,int,int,int,int,...) ; 
 int tuner_i2c_xfer_send (TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  tuner_warn (char*,int) ; 

__attribute__((used)) static int simple_set_tv_freq(struct dvb_frontend *fe,
			      struct analog_parameters *params)
{
	struct tuner_simple_priv *priv = fe->tuner_priv;
	u8 config, cb;
	u16 div;
	u8 buffer[4];
	int rc, IFPCoff, i;
	enum param_type desired_type;
	struct tuner_params *t_params;

	/* IFPCoff = Video Intermediate Frequency - Vif:
		940  =16*58.75  NTSC/J (Japan)
		732  =16*45.75  M/N STD
		704  =16*44     ATSC (at DVB code)
		632  =16*39.50  I U.K.
		622.4=16*38.90  B/G D/K I, L STD
		592  =16*37.00  D China
		590  =16.36.875 B Australia
		543.2=16*33.95  L' STD
		171.2=16*10.70  FM Radio (at set_radio_freq)
	*/

	if (params->std == V4L2_STD_NTSC_M_JP) {
		IFPCoff      = 940;
		desired_type = TUNER_PARAM_TYPE_NTSC;
	} else if ((params->std & V4L2_STD_MN) &&
		  !(params->std & ~V4L2_STD_MN)) {
		IFPCoff      = 732;
		desired_type = TUNER_PARAM_TYPE_NTSC;
	} else if (params->std == V4L2_STD_SECAM_LC) {
		IFPCoff      = 543;
		desired_type = TUNER_PARAM_TYPE_SECAM;
	} else {
		IFPCoff      = 623;
		desired_type = TUNER_PARAM_TYPE_PAL;
	}

	t_params = simple_tuner_params(fe, desired_type);

	i = simple_config_lookup(fe, t_params, &params->frequency,
				 &config, &cb);

	div = params->frequency + IFPCoff + offset;

	tuner_dbg("Freq= %d.%02d MHz, V_IF=%d.%02d MHz, Offset=%d.%02d MHz, div=%0d\n",
		  params->frequency / 16, params->frequency % 16 * 100 / 16,
		  IFPCoff / 16, IFPCoff % 16 * 100 / 16,
		  offset / 16, offset % 16 * 100 / 16, div);

	/* tv norm specific stuff for multi-norm tuners */
	simple_std_setup(fe, params, &config, &cb);

	if (t_params->cb_first_if_lower_freq && div < priv->last_div) {
		buffer[0] = config;
		buffer[1] = cb;
		buffer[2] = (div>>8) & 0x7f;
		buffer[3] = div      & 0xff;
	} else {
		buffer[0] = (div>>8) & 0x7f;
		buffer[1] = div      & 0xff;
		buffer[2] = config;
		buffer[3] = cb;
	}
	priv->last_div = div;
	if (t_params->has_tda9887) {
		struct v4l2_priv_tun_config tda9887_cfg;
		int tda_config = 0;
		int is_secam_l = (params->std & (V4L2_STD_SECAM_L |
						 V4L2_STD_SECAM_LC)) &&
			!(params->std & ~(V4L2_STD_SECAM_L |
					  V4L2_STD_SECAM_LC));

		tda9887_cfg.tuner = TUNER_TDA9887;
		tda9887_cfg.priv  = &tda_config;

		if (params->std == V4L2_STD_SECAM_LC) {
			if (t_params->port1_active ^ t_params->port1_invert_for_secam_lc)
				tda_config |= TDA9887_PORT1_ACTIVE;
			if (t_params->port2_active ^ t_params->port2_invert_for_secam_lc)
				tda_config |= TDA9887_PORT2_ACTIVE;
		} else {
			if (t_params->port1_active)
				tda_config |= TDA9887_PORT1_ACTIVE;
			if (t_params->port2_active)
				tda_config |= TDA9887_PORT2_ACTIVE;
		}
		if (t_params->intercarrier_mode)
			tda_config |= TDA9887_INTERCARRIER;
		if (is_secam_l) {
			if (i == 0 && t_params->default_top_secam_low)
				tda_config |= TDA9887_TOP(t_params->default_top_secam_low);
			else if (i == 1 && t_params->default_top_secam_mid)
				tda_config |= TDA9887_TOP(t_params->default_top_secam_mid);
			else if (t_params->default_top_secam_high)
				tda_config |= TDA9887_TOP(t_params->default_top_secam_high);
		} else {
			if (i == 0 && t_params->default_top_low)
				tda_config |= TDA9887_TOP(t_params->default_top_low);
			else if (i == 1 && t_params->default_top_mid)
				tda_config |= TDA9887_TOP(t_params->default_top_mid);
			else if (t_params->default_top_high)
				tda_config |= TDA9887_TOP(t_params->default_top_high);
		}
		if (t_params->default_pll_gating_18)
			tda_config |= TDA9887_GATING_18;
		i2c_clients_command(priv->i2c_props.adap, TUNER_SET_CONFIG,
				    &tda9887_cfg);
	}
	tuner_dbg("tv 0x%02x 0x%02x 0x%02x 0x%02x\n",
		  buffer[0], buffer[1], buffer[2], buffer[3]);

	rc = tuner_i2c_xfer_send(&priv->i2c_props, buffer, 4);
	if (4 != rc)
		tuner_warn("i2c i/o error: rc == %d (should be 4)\n", rc);

	simple_post_tune(fe, &buffer[0], div, config, cb);

	return 0;
}