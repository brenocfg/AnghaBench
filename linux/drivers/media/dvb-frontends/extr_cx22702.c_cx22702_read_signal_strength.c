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
struct dvb_frontend {struct cx22702_state* demodulator_priv; } ;
struct cx22702_state {int dummy; } ;

/* Variables and functions */
 int cx22702_readreg (struct cx22702_state*,int) ; 

__attribute__((used)) static int cx22702_read_signal_strength(struct dvb_frontend *fe,
	u16 *signal_strength)
{
	struct cx22702_state *state = fe->demodulator_priv;
	u8 reg23;

	/*
	 * Experience suggests that the strength signal register works as
	 * follows:
	 * - In the absence of signal, value is 0xff.
	 * - In the presence of a weak signal, bit 7 is set, not sure what
	 *   the lower 7 bits mean.
	 * - In the presence of a strong signal, the register holds a 7-bit
	 *   value (bit 7 is cleared), with greater values standing for
	 *   weaker signals.
	 */
	reg23 = cx22702_readreg(state, 0x23);
	if (reg23 & 0x80) {
		*signal_strength = 0;
	} else {
		reg23 = ~reg23 & 0x7f;
		/* Scale to 16 bit */
		*signal_strength = (reg23 << 9) | (reg23 << 2) | (reg23 >> 5);
	}

	return 0;
}