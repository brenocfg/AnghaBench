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
struct m88rs2000_state {int dummy; } ;
struct dvb_frontend {struct m88rs2000_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  m88rs2000_writereg (struct m88rs2000_state*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int m88rs2000_i2c_gate_ctrl(struct dvb_frontend *fe, int enable)
{
	struct m88rs2000_state *state = fe->demodulator_priv;

	if (enable)
		m88rs2000_writereg(state, 0x81, 0x84);
	else
		m88rs2000_writereg(state, 0x81, 0x81);
	udelay(10);
	return 0;
}