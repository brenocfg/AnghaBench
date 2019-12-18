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
struct stv0288_state {int dummy; } ;
struct dvb_frontend {struct stv0288_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  stv0288_writeregI (struct stv0288_state*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int stv0288_i2c_gate_ctrl(struct dvb_frontend *fe, int enable)
{
	struct stv0288_state *state = fe->demodulator_priv;

	if (enable)
		stv0288_writeregI(state, 0x01, 0xb5);
	else
		stv0288_writeregI(state, 0x01, 0x35);

	udelay(1);

	return 0;
}