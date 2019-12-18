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
struct stv0288_state {int dummy; } ;
struct dvb_frontend {struct stv0288_state* demodulator_priv; } ;
typedef  enum fe_sec_tone_mode { ____Placeholder_fe_sec_tone_mode } fe_sec_tone_mode ;

/* Variables and functions */
 int EINVAL ; 
 int EREMOTEIO ; 
#define  SEC_TONE_OFF 129 
#define  SEC_TONE_ON 128 
 int /*<<< orphan*/  stv0288_writeregI (struct stv0288_state*,int,int) ; 

__attribute__((used)) static int stv0288_set_tone(struct dvb_frontend *fe, enum fe_sec_tone_mode tone)
{
	struct stv0288_state *state = fe->demodulator_priv;

	switch (tone) {
	case SEC_TONE_ON:
		if (stv0288_writeregI(state, 0x05, 0x10))/* cont carrier */
			return -EREMOTEIO;
	break;

	case SEC_TONE_OFF:
		if (stv0288_writeregI(state, 0x05, 0x12))/* burst mode off*/
			return -EREMOTEIO;
	break;

	default:
		return -EINVAL;
	}
	return 0;
}