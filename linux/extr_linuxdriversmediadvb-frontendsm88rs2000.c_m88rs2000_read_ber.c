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
typedef  int u32 ;
struct m88rs2000_state {int dummy; } ;
struct dvb_frontend {struct m88rs2000_state* demodulator_priv; } ;

/* Variables and functions */
 int m88rs2000_readreg (struct m88rs2000_state*,int) ; 
 int /*<<< orphan*/  m88rs2000_writereg (struct m88rs2000_state*,int,int) ; 

__attribute__((used)) static int m88rs2000_read_ber(struct dvb_frontend *fe, u32 *ber)
{
	struct m88rs2000_state *state = fe->demodulator_priv;
	u8 tmp0, tmp1;

	m88rs2000_writereg(state, 0x9a, 0x30);
	tmp0 = m88rs2000_readreg(state, 0xd8);
	if ((tmp0 & 0x10) != 0) {
		m88rs2000_writereg(state, 0x9a, 0xb0);
		*ber = 0xffffffff;
		return 0;
	}

	*ber = (m88rs2000_readreg(state, 0xd7) << 8) |
		m88rs2000_readreg(state, 0xd6);

	tmp1 = m88rs2000_readreg(state, 0xd9);
	m88rs2000_writereg(state, 0xd9, (tmp1 & ~7) | 4);
	/* needs twice */
	m88rs2000_writereg(state, 0xd8, (tmp0 & ~8) | 0x30);
	m88rs2000_writereg(state, 0xd8, (tmp0 & ~8) | 0x30);
	m88rs2000_writereg(state, 0x9a, 0xb0);

	return 0;
}