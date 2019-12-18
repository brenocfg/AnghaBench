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
struct s5h1409_state {int qam_state; } ;
struct dvb_frontend {struct s5h1409_state* demodulator_priv; } ;

/* Variables and functions */
 int s5h1409_readreg (struct s5h1409_state*,int) ; 
 int /*<<< orphan*/  s5h1409_writereg (struct s5h1409_state*,int,int) ; 

__attribute__((used)) static void s5h1409_set_qam_interleave_mode_legacy(struct dvb_frontend *fe)
{
	struct s5h1409_state *state = fe->demodulator_priv;
	u16 reg, reg1, reg2;

	reg = s5h1409_readreg(state, 0xf1);

	/* Master lock */
	if ((reg >> 15) & 0x1) {
		if (state->qam_state != 2) {
			state->qam_state = 2;
			reg1 = s5h1409_readreg(state, 0xb2);
			reg2 = s5h1409_readreg(state, 0xad);

			s5h1409_writereg(state, 0x96, 0x20);
			s5h1409_writereg(state, 0xad,
				(((reg1 & 0xf000) >> 4) | (reg2 & 0xf0ff)));
			s5h1409_writereg(state, 0xab,
				s5h1409_readreg(state, 0xab) & 0xeffe);
		}
	} else {
		if (state->qam_state != 1) {
			state->qam_state = 1;
			s5h1409_writereg(state, 0x96, 0x08);
			s5h1409_writereg(state, 0xab,
				s5h1409_readreg(state, 0xab) | 0x1001);
		}
	}
}