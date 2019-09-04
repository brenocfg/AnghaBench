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
typedef  int /*<<< orphan*/  u16 ;
typedef  scalar_t__ timf ;
struct dvb_frontend {struct dib8000_state* demodulator_priv; } ;
struct dib8000_state {scalar_t__ timf; int timf_default; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*) ; 

__attribute__((used)) static int dib8000_set_bandwidth(struct dvb_frontend *fe, u32 bw)
{
	struct dib8000_state *state = fe->demodulator_priv;
	u32 timf;

	if (bw == 0)
		bw = 6000;

	if (state->timf == 0) {
		dprintk("using default timf\n");
		timf = state->timf_default;
	} else {
		dprintk("using updated timf\n");
		timf = state->timf;
	}

	dib8000_write_word(state, 29, (u16) ((timf >> 16) & 0xffff));
	dib8000_write_word(state, 30, (u16) ((timf) & 0xffff));

	return 0;
}