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
struct mt352_state {int dummy; } ;
struct dvb_frontend {struct mt352_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGC_GAIN_0 ; 
 int /*<<< orphan*/  AGC_GAIN_1 ; 
 int mt352_read_register (struct mt352_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt352_read_signal_strength(struct dvb_frontend* fe, u16* strength)
{
	struct mt352_state* state = fe->demodulator_priv;

	/* align the 12 bit AGC gain with the most significant bits */
	u16 signal = ((mt352_read_register(state, AGC_GAIN_1) & 0x0f) << 12) |
		(mt352_read_register(state, AGC_GAIN_0) << 4);

	/* inverse of gain is signal strength */
	*strength = ~signal;
	return 0;
}