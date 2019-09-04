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
struct s5h1432_state {int dummy; } ;
struct dvb_frontend {struct s5h1432_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  S5H1432_I2C_TOP_ADDR ; 
 int s5h1432_readreg (struct s5h1432_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s5h1432_writereg (struct s5h1432_state*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int s5h1432_set_channel_bandwidth(struct dvb_frontend *fe,
					 u32 bandwidth)
{
	struct s5h1432_state *state = fe->demodulator_priv;

	u8 reg = 0;

	/* Register [0x2E] bit 3:2 : 8MHz = 0; 7MHz = 1; 6MHz = 2 */
	reg = s5h1432_readreg(state, S5H1432_I2C_TOP_ADDR, 0x2E);
	reg &= ~(0x0C);
	switch (bandwidth) {
	case 6:
		reg |= 0x08;
		break;
	case 7:
		reg |= 0x04;
		break;
	case 8:
		reg |= 0x00;
		break;
	default:
		return 0;
	}
	s5h1432_writereg(state, S5H1432_I2C_TOP_ADDR, 0x2E, reg);
	return 1;
}