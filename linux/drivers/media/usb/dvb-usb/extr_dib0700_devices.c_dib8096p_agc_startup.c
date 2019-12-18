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
typedef  int u16 ;
struct dvb_usb_adapter {int /*<<< orphan*/  dev; struct dib0700_adapter_state* priv; } ;
struct TYPE_5__ {int bandwidth_hz; } ;
struct dvb_frontend {TYPE_2__ dtv_property_cache; TYPE_1__* dvb; } ;
struct dibx090p_best_adc {int /*<<< orphan*/  timf; int /*<<< orphan*/  pll_prediv; int /*<<< orphan*/  pll_loopdiv; } ;
struct dibx000_bandwidth_config {int /*<<< orphan*/  pll_prediv; int /*<<< orphan*/  pll_ratio; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* ctrl_timf ) (struct dvb_frontend*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* update_pll ) (struct dvb_frontend*,struct dibx000_bandwidth_config*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_wbd_ref ) (struct dvb_frontend*,int) ;} ;
struct dib0700_adapter_state {int (* set_param_save ) (struct dvb_frontend*) ;TYPE_3__ dib8000_ops; } ;
struct TYPE_4__ {struct dvb_usb_adapter* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEMOD_TIMF_SET ; 
 int dib0090_get_wbd_target (struct dvb_frontend*) ; 
 int /*<<< orphan*/  dib0090_pwm_gain_reset (struct dvb_frontend*) ; 
 int /*<<< orphan*/  dib0700_set_i2c_speed (int /*<<< orphan*/ ,int) ; 
 scalar_t__ dib8096p_get_best_sampling (struct dvb_frontend*,struct dibx090p_best_adc*) ; 
 int /*<<< orphan*/  memset (struct dibx000_bandwidth_config*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct dvb_frontend*) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub3 (struct dvb_frontend*,struct dibx000_bandwidth_config*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct dvb_frontend*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dib8096p_agc_startup(struct dvb_frontend *fe)
{
	struct dvb_usb_adapter *adap = fe->dvb->priv;
	struct dib0700_adapter_state *state = adap->priv;
	struct dibx000_bandwidth_config pll;
	struct dibx090p_best_adc adc;
	u16 target;
	int ret;

	ret = state->set_param_save(fe);
	if (ret < 0)
		return ret;
	memset(&pll, 0, sizeof(struct dibx000_bandwidth_config));

	dib0090_pwm_gain_reset(fe);
	/* dib0090_get_wbd_target is returning any possible
	   temperature compensated wbd-target */
	target = (dib0090_get_wbd_target(fe) * 8  + 1) / 2;
	state->dib8000_ops.set_wbd_ref(fe, target);

	if (dib8096p_get_best_sampling(fe, &adc) == 0) {
		pll.pll_ratio  = adc.pll_loopdiv;
		pll.pll_prediv = adc.pll_prediv;

		dib0700_set_i2c_speed(adap->dev, 200);
		state->dib8000_ops.update_pll(fe, &pll, fe->dtv_property_cache.bandwidth_hz / 1000, 0);
		state->dib8000_ops.ctrl_timf(fe, DEMOD_TIMF_SET, adc.timf);
		dib0700_set_i2c_speed(adap->dev, 1000);
	}
	return 0;
}