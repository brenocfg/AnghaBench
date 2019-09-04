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
struct dvb_frontend {struct dib7000p_state* demodulator_priv; } ;
struct dib7000p_state {scalar_t__ version; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIB7000P_POWER_INTERFACE_ONLY ; 
 int /*<<< orphan*/  OUTMODE_HIGH_Z ; 
 scalar_t__ SOC7090 ; 
 int dib7000p_set_output_mode (struct dib7000p_state*,int /*<<< orphan*/ ) ; 
 int dib7000p_set_power_mode (struct dib7000p_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dib7000p_sleep(struct dvb_frontend *demod)
{
	struct dib7000p_state *state = demod->demodulator_priv;
	if (state->version == SOC7090)
		return dib7000p_set_power_mode(state, DIB7000P_POWER_INTERFACE_ONLY);
	return dib7000p_set_output_mode(state, OUTMODE_HIGH_Z) | dib7000p_set_power_mode(state, DIB7000P_POWER_INTERFACE_ONLY);
}