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
typedef  int u8 ;
struct m88rs2000_state {int dummy; } ;
struct dvb_frontend {struct m88rs2000_state* demodulator_priv; } ;
typedef  enum fe_sec_voltage { ____Placeholder_fe_sec_voltage } fe_sec_voltage ;

/* Variables and functions */
#define  SEC_VOLTAGE_13 130 
#define  SEC_VOLTAGE_18 129 
#define  SEC_VOLTAGE_OFF 128 
 int m88rs2000_readreg (struct m88rs2000_state*,int) ; 
 int /*<<< orphan*/  m88rs2000_writereg (struct m88rs2000_state*,int,int) ; 

__attribute__((used)) static int m88rs2000_set_voltage(struct dvb_frontend *fe,
				 enum fe_sec_voltage volt)
{
	struct m88rs2000_state *state = fe->demodulator_priv;
	u8 data;

	data = m88rs2000_readreg(state, 0xb2);
	data |= 0x03; /* bit0 V/H, bit1 off/on */

	switch (volt) {
	case SEC_VOLTAGE_18:
		data &= ~0x03;
		break;
	case SEC_VOLTAGE_13:
		data &= ~0x03;
		data |= 0x01;
		break;
	case SEC_VOLTAGE_OFF:
		break;
	}

	m88rs2000_writereg(state, 0xb2, data);

	return 0;
}