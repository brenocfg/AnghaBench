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

/* Variables and functions */
 int /*<<< orphan*/  R367TER_PLLMDIV ; 
 int /*<<< orphan*/  R367TER_PLLNDIV ; 
 int /*<<< orphan*/  R367TER_PLLSETUP ; 
#define  STV0367_ICSPEED_53125 129 
#define  STV0367_ICSPEED_58000 128 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  stv0367_writereg (struct stv0367_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stv0367_pll_setup(struct stv0367_state *state,
				u32 icspeed, u32 xtal)
{
	/* note on regs: R367TER_* and R367CAB_* defines each point to
	 * 0xf0d8, so just use R367TER_ for both cases
	 */

	switch (icspeed) {
	case STV0367_ICSPEED_58000:
		switch (xtal) {
		default:
		case 27000000:
			dprintk("STV0367 SetCLKgen for 58MHz IC and 27Mhz crystal\n");
			/* PLLMDIV: 27, PLLNDIV: 232 */
			stv0367_writereg(state, R367TER_PLLMDIV, 0x1b);
			stv0367_writereg(state, R367TER_PLLNDIV, 0xe8);
			break;
		}
		break;
	default:
	case STV0367_ICSPEED_53125:
		switch (xtal) {
			/* set internal freq to 53.125MHz */
		case 16000000:
			stv0367_writereg(state, R367TER_PLLMDIV, 0x2);
			stv0367_writereg(state, R367TER_PLLNDIV, 0x1b);
			break;
		case 25000000:
			stv0367_writereg(state, R367TER_PLLMDIV, 0xa);
			stv0367_writereg(state, R367TER_PLLNDIV, 0x55);
			break;
		default:
		case 27000000:
			dprintk("FE_STV0367TER_SetCLKgen for 27Mhz\n");
			stv0367_writereg(state, R367TER_PLLMDIV, 0x1);
			stv0367_writereg(state, R367TER_PLLNDIV, 0x8);
			break;
		case 30000000:
			stv0367_writereg(state, R367TER_PLLMDIV, 0xc);
			stv0367_writereg(state, R367TER_PLLNDIV, 0x55);
			break;
		}
	}

	stv0367_writereg(state, R367TER_PLLSETUP, 0x18);
}