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
struct ttusbdecfe_state {int voltage; } ;
struct dvb_frontend {scalar_t__ demodulator_priv; } ;
typedef  enum fe_sec_voltage { ____Placeholder_fe_sec_voltage } fe_sec_voltage ;

/* Variables and functions */
 int EINVAL ; 
#define  SEC_VOLTAGE_13 129 
#define  SEC_VOLTAGE_18 128 

__attribute__((used)) static int ttusbdecfe_dvbs_set_voltage(struct dvb_frontend *fe,
				       enum fe_sec_voltage voltage)
{
	struct ttusbdecfe_state* state = (struct ttusbdecfe_state*) fe->demodulator_priv;

	switch (voltage) {
	case SEC_VOLTAGE_13:
		state->voltage = 13;
		break;
	case SEC_VOLTAGE_18:
		state->voltage = 18;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}