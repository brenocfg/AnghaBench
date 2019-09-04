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
typedef  enum fe_sec_tone_mode { ____Placeholder_fe_sec_tone_mode } fe_sec_tone_mode ;

/* Variables and functions */
#define  SEC_TONE_OFF 129 
#define  SEC_TONE_ON 128 
 int m88rs2000_readreg (struct m88rs2000_state*,int) ; 
 int /*<<< orphan*/  m88rs2000_writereg (struct m88rs2000_state*,int,int) ; 

__attribute__((used)) static int m88rs2000_set_tone(struct dvb_frontend *fe,
			      enum fe_sec_tone_mode tone)
{
	struct m88rs2000_state *state = fe->demodulator_priv;
	u8 reg0, reg1;
	m88rs2000_writereg(state, 0x9a, 0x30);
	reg0 = m88rs2000_readreg(state, 0xb1);
	reg1 = m88rs2000_readreg(state, 0xb2);

	reg1 &= 0x3f;

	switch (tone) {
	case SEC_TONE_ON:
		reg0 |= 0x4;
		reg0 &= 0xbc;
		break;
	case SEC_TONE_OFF:
		reg1 |= 0x80;
		break;
	default:
		break;
	}
	m88rs2000_writereg(state, 0xb2, reg1);
	m88rs2000_writereg(state, 0xb1, reg0);
	m88rs2000_writereg(state, 0x9a, 0xb0);
	return 0;
}