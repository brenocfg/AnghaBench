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
typedef  int u16 ;
struct dvb_frontend {struct cx24110_state* demodulator_priv; } ;
struct cx24110_state {int dummy; } ;

/* Variables and functions */
 int cx24110_readreg (struct cx24110_state*,int) ; 

__attribute__((used)) static int cx24110_read_signal_strength(struct dvb_frontend* fe, u16* signal_strength)
{
	struct cx24110_state *state = fe->demodulator_priv;

/* no provision in hardware. Read the frontend AGC accumulator. No idea how to scale this, but I know it is 2s complement */
	u8 signal = cx24110_readreg (state, 0x27)+128;
	*signal_strength = (signal << 8) | signal;

	return 0;
}