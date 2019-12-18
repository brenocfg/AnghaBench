#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dvb_frontend {struct dib7000m_state* demodulator_priv; } ;
struct dib7000m_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIB7000M_POWER_ALL ; 
 int /*<<< orphan*/  DIBX000_SLOW_ADC_ON ; 
 scalar_t__ dib7000m_set_adc_state (struct dib7000m_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib7000m_set_power_mode (struct dib7000m_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*) ; 

__attribute__((used)) static int dib7000m_wakeup(struct dvb_frontend *demod)
{
	struct dib7000m_state *state = demod->demodulator_priv;

	dib7000m_set_power_mode(state, DIB7000M_POWER_ALL);

	if (dib7000m_set_adc_state(state, DIBX000_SLOW_ADC_ON) != 0)
		dprintk("could not start Slow ADC\n");

	return 0;
}