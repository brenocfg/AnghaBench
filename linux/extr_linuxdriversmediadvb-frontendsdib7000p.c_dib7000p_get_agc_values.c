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
typedef  int /*<<< orphan*/  u16 ;
struct dvb_frontend {struct dib7000p_state* demodulator_priv; } ;
struct dib7000p_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib7000p_read_word (struct dib7000p_state*,int) ; 

__attribute__((used)) static int dib7000p_get_agc_values(struct dvb_frontend *fe,
		u16 *agc_global, u16 *agc1, u16 *agc2, u16 *wbd)
{
	struct dib7000p_state *state = fe->demodulator_priv;

	if (agc_global != NULL)
		*agc_global = dib7000p_read_word(state, 394);
	if (agc1 != NULL)
		*agc1 = dib7000p_read_word(state, 392);
	if (agc2 != NULL)
		*agc2 = dib7000p_read_word(state, 393);
	if (wbd != NULL)
		*wbd = dib7000p_read_word(state, 397);

	return 0;
}