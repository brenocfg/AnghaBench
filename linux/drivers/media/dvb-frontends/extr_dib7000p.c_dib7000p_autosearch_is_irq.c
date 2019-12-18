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
struct dvb_frontend {struct dib7000p_state* demodulator_priv; } ;
struct dib7000p_state {int dummy; } ;

/* Variables and functions */
 int dib7000p_read_word (struct dib7000p_state*,int) ; 

__attribute__((used)) static int dib7000p_autosearch_is_irq(struct dvb_frontend *demod)
{
	struct dib7000p_state *state = demod->demodulator_priv;
	u16 irq_pending = dib7000p_read_word(state, 1284);

	if (irq_pending & 0x1)
		return 1;

	if (irq_pending & 0x2)
		return 2;

	return 0;
}