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
struct dvb_frontend {struct cx24123_state* demodulator_priv; } ;
struct cx24123_state {int dummy; } ;

/* Variables and functions */
 int cx24123_readreg (struct cx24123_state*,int) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 

__attribute__((used)) static int cx24123_read_signal_strength(struct dvb_frontend *fe,
	u16 *signal_strength)
{
	struct cx24123_state *state = fe->demodulator_priv;

	/* larger = better */
	*signal_strength = cx24123_readreg(state, 0x3b) << 8;

	dprintk("Signal strength = %d\n", *signal_strength);

	return 0;
}