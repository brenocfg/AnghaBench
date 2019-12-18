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
typedef  short u16 ;
struct nxt6000_state {int dummy; } ;
struct dvb_frontend {struct nxt6000_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGC_GAIN_1 ; 
 int /*<<< orphan*/  AGC_GAIN_2 ; 
 int nxt6000_readreg (struct nxt6000_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nxt6000_read_signal_strength(struct dvb_frontend* fe, u16* signal_strength)
{
	struct nxt6000_state* state = fe->demodulator_priv;

	*signal_strength = (short) (511 -
		(nxt6000_readreg(state, AGC_GAIN_1) +
		((nxt6000_readreg(state, AGC_GAIN_2) & 0x03) << 8)));

	return 0;
}