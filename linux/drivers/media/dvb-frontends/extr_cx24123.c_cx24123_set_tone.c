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
struct dvb_frontend {struct cx24123_state* demodulator_priv; } ;
struct cx24123_state {int dummy; } ;
typedef  enum fe_sec_tone_mode { ____Placeholder_fe_sec_tone_mode } fe_sec_tone_mode ;

/* Variables and functions */
 int EINVAL ; 
#define  SEC_TONE_OFF 129 
#define  SEC_TONE_ON 128 
 int cx24123_readreg (struct cx24123_state*,int) ; 
 int /*<<< orphan*/  cx24123_wait_for_diseqc (struct cx24123_state*) ; 
 int cx24123_writereg (struct cx24123_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  err (char*,int) ; 

__attribute__((used)) static int cx24123_set_tone(struct dvb_frontend *fe, enum fe_sec_tone_mode tone)
{
	struct cx24123_state *state = fe->demodulator_priv;
	u8 val;

	/* wait for diseqc queue ready */
	cx24123_wait_for_diseqc(state);

	val = cx24123_readreg(state, 0x29) & ~0x40;

	switch (tone) {
	case SEC_TONE_ON:
		dprintk("setting tone on\n");
		return cx24123_writereg(state, 0x29, val | 0x10);
	case SEC_TONE_OFF:
		dprintk("setting tone off\n");
		return cx24123_writereg(state, 0x29, val & 0xef);
	default:
		err("CASE reached default with tone=%d\n", tone);
		return -EINVAL;
	}

	return 0;
}