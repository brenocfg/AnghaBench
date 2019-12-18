#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct dvb_usb_adapter {struct dib0700_adapter_state* priv; } ;
struct TYPE_5__ {int frequency; int bandwidth_hz; } ;
struct dvb_frontend {TYPE_2__ dtv_property_cache; TYPE_1__* dvb; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_tune_state ) (struct dvb_frontend*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* pwm_agc_reset ) (struct dvb_frontend*) ;int /*<<< orphan*/  (* set_gpio ) (struct dvb_frontend*,int,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* set_wbd_ref ) (struct dvb_frontend*,int) ;int /*<<< orphan*/  (* ctrl_timf ) (struct dvb_frontend*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* update_pll ) (struct dvb_frontend*,int /*<<< orphan*/ *,int,int) ;} ;
struct dib0700_adapter_state {int (* set_param_save ) (struct dvb_frontend*) ;TYPE_3__ dib8000_ops; } ;
typedef  enum frontend_tune_state { ____Placeholder_frontend_tune_state } frontend_tune_state ;
struct TYPE_4__ {struct dvb_usb_adapter* priv; } ;

/* Variables and functions */
 int BAND_CBAND ; 
 int BAND_OF_FREQUENCY (int) ; 
#define  BAND_UHF 129 
#define  BAND_VHF 128 
 int /*<<< orphan*/  CT_AGC_START ; 
 int CT_AGC_STEP_0 ; 
 int CT_AGC_STEP_1 ; 
 int CT_AGC_STOP ; 
 int /*<<< orphan*/  CT_DEMOD_START ; 
 int CT_SHUTDOWN ; 
 int /*<<< orphan*/  DEMOD_TIMF_SET ; 
 int EINVAL ; 
 int /*<<< orphan*/  deb_info (char*,...) ; 
 int dib0090_gain_control (struct dvb_frontend*) ; 
 int /*<<< orphan*/  dib0090_get_current_gain (struct dvb_frontend*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*) ; 
 int dib0090_get_tune_state (struct dvb_frontend*) ; 
 int dib0090_get_wbd_target (struct dvb_frontend*) ; 
 int /*<<< orphan*/  dib0090_pwm_gain_reset (struct dvb_frontend*) ; 
 int /*<<< orphan*/  dib0090_set_tune_state (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int dib8090_compute_pll_parameters (struct dvb_frontend*) ; 
 int /*<<< orphan*/  dib8090_pll_config_12mhz ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub10 (struct dvb_frontend*) ; 
 int /*<<< orphan*/  stub11 (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int,int /*<<< orphan*/ ,int) ; 
 int stub3 (struct dvb_frontend*) ; 
 int /*<<< orphan*/  stub4 (struct dvb_frontend*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  stub5 (struct dvb_frontend*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  stub6 (struct dvb_frontend*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub8 (struct dvb_frontend*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub9 (struct dvb_frontend*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dib8096_set_param_override(struct dvb_frontend *fe)
{
	struct dvb_usb_adapter *adap = fe->dvb->priv;
	struct dib0700_adapter_state *state = adap->priv;
	u8 pll_ratio, band = BAND_OF_FREQUENCY(fe->dtv_property_cache.frequency / 1000);
	u16 target, ltgain, rf_gain_limit;
	u32 timf;
	int ret = 0;
	enum frontend_tune_state tune_state = CT_SHUTDOWN;

	switch (band) {
	default:
			deb_info("Warning : Rf frequency  (%iHz) is not in the supported range, using VHF switch ", fe->dtv_property_cache.frequency);
			/* fall through */
	case BAND_VHF:
			state->dib8000_ops.set_gpio(fe, 3, 0, 1);
			break;
	case BAND_UHF:
			state->dib8000_ops.set_gpio(fe, 3, 0, 0);
			break;
	}

	ret = state->set_param_save(fe);
	if (ret < 0)
		return ret;

	if (fe->dtv_property_cache.bandwidth_hz != 6000000) {
		deb_info("only 6MHz bandwidth is supported\n");
		return -EINVAL;
	}

	/* Update PLL if needed ratio */
	state->dib8000_ops.update_pll(fe, &dib8090_pll_config_12mhz, fe->dtv_property_cache.bandwidth_hz / 1000, 0);

	/* Get optimize PLL ratio to remove spurious */
	pll_ratio = dib8090_compute_pll_parameters(fe);
	if (pll_ratio == 17)
		timf = 21387946;
	else if (pll_ratio == 18)
		timf = 20199727;
	else if (pll_ratio == 19)
		timf = 19136583;
	else
		timf = 18179756;

	/* Update ratio */
	state->dib8000_ops.update_pll(fe, &dib8090_pll_config_12mhz, fe->dtv_property_cache.bandwidth_hz / 1000, pll_ratio);

	state->dib8000_ops.ctrl_timf(fe, DEMOD_TIMF_SET, timf);

	if (band != BAND_CBAND) {
		/* dib0090_get_wbd_target is returning any possible temperature compensated wbd-target */
		target = (dib0090_get_wbd_target(fe) * 8 * 18 / 33 + 1) / 2;
		state->dib8000_ops.set_wbd_ref(fe, target);
	}

	if (band == BAND_CBAND) {
		deb_info("tuning in CBAND - soft-AGC startup\n");
		dib0090_set_tune_state(fe, CT_AGC_START);

		do {
			ret = dib0090_gain_control(fe);
			msleep(ret);
			tune_state = dib0090_get_tune_state(fe);
			if (tune_state == CT_AGC_STEP_0)
				state->dib8000_ops.set_gpio(fe, 6, 0, 1);
			else if (tune_state == CT_AGC_STEP_1) {
				dib0090_get_current_gain(fe, NULL, NULL, &rf_gain_limit, &ltgain);
				if (rf_gain_limit < 2000) /* activate the external attenuator in case of very high input power */
					state->dib8000_ops.set_gpio(fe, 6, 0, 0);
			}
		} while (tune_state < CT_AGC_STOP);

		deb_info("switching to PWM AGC\n");
		dib0090_pwm_gain_reset(fe);
		state->dib8000_ops.pwm_agc_reset(fe);
		state->dib8000_ops.set_tune_state(fe, CT_DEMOD_START);
	} else {
		/* for everything else than CBAND we are using standard AGC */
		deb_info("not tuning in CBAND - standard AGC startup\n");
		dib0090_pwm_gain_reset(fe);
	}

	return 0;
}