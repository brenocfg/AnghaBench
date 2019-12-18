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
struct dvb_frontend {struct dib3000mc_state* demodulator_priv; } ;
struct dib3000mc_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib3000mc_write_word (struct dib3000mc_state*,int,int) ; 

__attribute__((used)) static int dib3000mc_sleep(struct dvb_frontend *demod)
{
	struct dib3000mc_state *state = demod->demodulator_priv;

	dib3000mc_write_word(state, 1031, 0xFFFF);
	dib3000mc_write_word(state, 1032, 0xFFFF);
	dib3000mc_write_word(state, 1033, 0xFFF0);

	return 0;
}