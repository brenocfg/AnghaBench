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
typedef  int u32 ;
struct dvb_frontend {struct dib8000_state* demodulator_priv; } ;
struct dib8000_state {int revision; } ;

/* Variables and functions */
 int dib8000_read_word (struct dib8000_state*,int) ; 

__attribute__((used)) static int dib8000_read_ber(struct dvb_frontend *fe, u32 * ber)
{
	struct dib8000_state *state = fe->demodulator_priv;

	/* 13 segments */
	if (state->revision == 0x8090)
		*ber = (dib8000_read_word(state, 562) << 16) |
			dib8000_read_word(state, 563);
	else
		*ber = (dib8000_read_word(state, 560) << 16) |
			dib8000_read_word(state, 561);
	return 0;
}