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
typedef  scalar_t__ u8 ;
struct dvb_frontend {struct dib7000m_state* demodulator_priv; } ;
struct dib7000m_state {int div_sync_wait; scalar_t__ reg_offs; scalar_t__ div_state; scalar_t__ div_force_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib7000m_write_word (struct dib7000m_state*,scalar_t__,int) ; 
 int /*<<< orphan*/  dprintk (char*) ; 

__attribute__((used)) static int dib7000m_set_diversity_in(struct dvb_frontend *demod, int onoff)
{
	struct dib7000m_state *state = demod->demodulator_priv;

	if (state->div_force_off) {
		dprintk("diversity combination deactivated - forced by COFDM parameters\n");
		onoff = 0;
	}
	state->div_state = (u8)onoff;

	if (onoff) {
		dib7000m_write_word(state, 263 + state->reg_offs, 6);
		dib7000m_write_word(state, 264 + state->reg_offs, 6);
		dib7000m_write_word(state, 266 + state->reg_offs, (state->div_sync_wait << 4) | (1 << 2) | (2 << 0));
	} else {
		dib7000m_write_word(state, 263 + state->reg_offs, 1);
		dib7000m_write_word(state, 264 + state->reg_offs, 0);
		dib7000m_write_word(state, 266 + state->reg_offs, 0);
	}

	return 0;
}