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
struct dvb_frontend {struct dib8000_state* demodulator_priv; } ;
struct dib8000_state {int diversity_onoff; int revision; int /*<<< orphan*/  differential_constellation; } ;

/* Variables and functions */
 int dib8000_read_word (struct dib8000_state*,int) ; 
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int dib8000_set_diversity_in(struct dvb_frontend *fe, int onoff)
{
	struct dib8000_state *state = fe->demodulator_priv;
	u16 tmp, sync_wait = dib8000_read_word(state, 273) & 0xfff0;

	dprintk("set diversity input to %i\n", onoff);
	if (!state->differential_constellation) {
		dib8000_write_word(state, 272, 1 << 9);	//dvsy_off_lmod4 = 1
		dib8000_write_word(state, 273, sync_wait | (1 << 2) | 2);	// sync_enable = 1; comb_mode = 2
	} else {
		dib8000_write_word(state, 272, 0);	//dvsy_off_lmod4 = 0
		dib8000_write_word(state, 273, sync_wait);	// sync_enable = 0; comb_mode = 0
	}
	state->diversity_onoff = onoff;

	switch (onoff) {
	case 0:		/* only use the internal way - not the diversity input */
		dib8000_write_word(state, 270, 1);
		dib8000_write_word(state, 271, 0);
		break;
	case 1:		/* both ways */
		dib8000_write_word(state, 270, 6);
		dib8000_write_word(state, 271, 6);
		break;
	case 2:		/* only the diversity input */
		dib8000_write_word(state, 270, 0);
		dib8000_write_word(state, 271, 1);
		break;
	}

	if (state->revision == 0x8002) {
		tmp = dib8000_read_word(state, 903);
		dib8000_write_word(state, 903, tmp & ~(1 << 3));
		msleep(30);
		dib8000_write_word(state, 903, tmp | (1 << 3));
	}
	return 0;
}