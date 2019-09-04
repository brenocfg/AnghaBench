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
struct stv0299_state {scalar_t__ errmode; } ;
struct dvb_frontend {struct stv0299_state* demodulator_priv; } ;

/* Variables and functions */
 int ENOSYS ; 
 scalar_t__ STATUS_BER ; 
 int stv0299_readreg (struct stv0299_state*,int) ; 

__attribute__((used)) static int stv0299_read_ber(struct dvb_frontend* fe, u32* ber)
{
	struct stv0299_state* state = fe->demodulator_priv;

	if (state->errmode != STATUS_BER)
		return -ENOSYS;

	*ber = stv0299_readreg(state, 0x1e) | (stv0299_readreg(state, 0x1d) << 8);

	return 0;
}