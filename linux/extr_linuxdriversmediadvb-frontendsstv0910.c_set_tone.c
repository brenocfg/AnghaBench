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
typedef  int u16 ;
struct stv {scalar_t__ nr; } ;
struct dvb_frontend {struct stv* demodulator_priv; } ;
typedef  enum fe_sec_tone_mode { ____Placeholder_fe_sec_tone_mode } fe_sec_tone_mode ;

/* Variables and functions */
 int EINVAL ; 
 int RSTV0910_P1_DISTXCFG ; 
#define  SEC_TONE_OFF 129 
#define  SEC_TONE_ON 128 
 int write_reg (struct stv*,int,int) ; 

__attribute__((used)) static int set_tone(struct dvb_frontend *fe, enum fe_sec_tone_mode tone)
{
	struct stv *state = fe->demodulator_priv;
	u16 offs = state->nr ? 0x40 : 0;

	switch (tone) {
	case SEC_TONE_ON:
		return write_reg(state, RSTV0910_P1_DISTXCFG + offs, 0x38);
	case SEC_TONE_OFF:
		return write_reg(state, RSTV0910_P1_DISTXCFG + offs, 0x3a);
	default:
		break;
	}
	return -EINVAL;
}