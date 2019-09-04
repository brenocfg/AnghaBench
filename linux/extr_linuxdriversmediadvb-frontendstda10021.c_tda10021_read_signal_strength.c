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
struct tda10021_state {int dummy; } ;
struct dvb_frontend {struct tda10021_state* demodulator_priv; } ;

/* Variables and functions */
 int tda10021_readreg (struct tda10021_state*,int) ; 

__attribute__((used)) static int tda10021_read_signal_strength(struct dvb_frontend* fe, u16* strength)
{
	struct tda10021_state* state = fe->demodulator_priv;

	u8 config = tda10021_readreg(state, 0x02);
	u8 gain = tda10021_readreg(state, 0x17);
	if (config & 0x02)
		/* the agc value is inverted */
		gain = ~gain;
	*strength = (gain << 8) | gain;

	return 0;
}