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
typedef  int u32 ;
struct stv0288_state {scalar_t__ errmode; } ;
struct dvb_frontend {struct stv0288_state* demodulator_priv; } ;

/* Variables and functions */
 scalar_t__ STATUS_BER ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int stv0288_readreg (struct stv0288_state*,int) ; 

__attribute__((used)) static int stv0288_read_ber(struct dvb_frontend *fe, u32 *ber)
{
	struct stv0288_state *state = fe->demodulator_priv;

	if (state->errmode != STATUS_BER)
		return 0;
	*ber = (stv0288_readreg(state, 0x26) << 8) |
					stv0288_readreg(state, 0x27);
	dprintk("stv0288_read_ber %d\n", *ber);

	return 0;
}