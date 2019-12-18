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
struct TYPE_2__ {int frequency; } ;
struct dvb_frontend {TYPE_1__ dtv_property_cache; struct dib8000_state* demodulator_priv; } ;
struct dib8000_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAND_OF_FREQUENCY (int) ; 
 int /*<<< orphan*/  DIBX000_ADC_ON ; 
 int /*<<< orphan*/  dib8000_set_adc_state (struct dib8000_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib8000_set_agc_config (struct dib8000_state*,unsigned char) ; 

__attribute__((used)) static void dib8000_pwm_agc_reset(struct dvb_frontend *fe)
{
	struct dib8000_state *state = fe->demodulator_priv;
	dib8000_set_adc_state(state, DIBX000_ADC_ON);
	dib8000_set_agc_config(state, (unsigned char)(BAND_OF_FREQUENCY(fe->dtv_property_cache.frequency / 1000)));
}