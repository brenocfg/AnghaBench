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
 scalar_t__ cx24123_readreg (struct cx24123_state*,int) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 

__attribute__((used)) static int cx24123_read_snr(struct dvb_frontend *fe, u16 *snr)
{
	struct cx24123_state *state = fe->demodulator_priv;

	/* Inverted raw Es/N0 count, totally bogus but better than the
	   BER threshold. */
	*snr = 65535 - (((u16)cx24123_readreg(state, 0x18) << 8) |
			 (u16)cx24123_readreg(state, 0x19));

	dprintk("read S/N index = %d\n", *snr);

	return 0;
}