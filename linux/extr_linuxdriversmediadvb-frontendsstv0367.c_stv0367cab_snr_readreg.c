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
struct stv0367_state {int dummy; } ;
struct dvb_frontend {struct stv0367_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  F367CAB_SNR_HI ; 
 int /*<<< orphan*/  F367CAB_SNR_LO ; 
 int stv0367_readbits (struct stv0367_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stv0367cab_snr_readreg(struct dvb_frontend *fe, int avgdiv)
{
	struct stv0367_state *state = fe->demodulator_priv;
	u32 regval = 0;
	int i;

	for (i = 0; i < 10; i++) {
		regval += (stv0367_readbits(state, F367CAB_SNR_LO)
			+ 256 * stv0367_readbits(state, F367CAB_SNR_HI));
	}

	if (avgdiv)
		regval /= 10;

	return regval;
}