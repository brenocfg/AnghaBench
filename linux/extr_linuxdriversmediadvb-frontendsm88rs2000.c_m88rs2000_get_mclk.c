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
 int RS2000_FE_CRYSTAL_KHZ ; 
 int m88rs2000_readreg (struct m88rs2000_state*,int) ; 

__attribute__((used)) static u32 m88rs2000_get_mclk(struct dvb_frontend *fe)
{
	struct m88rs2000_state *state = fe->demodulator_priv;
	u32 mclk;
	u8 reg;
	/* Must not be 0x00 or 0xff */
	reg = m88rs2000_readreg(state, 0x86);
	if (!reg || reg == 0xff)
		return 0;

	reg /= 2;
	reg += 1;

	mclk = (u32)(reg * RS2000_FE_CRYSTAL_KHZ + 28 / 2) / 28;

	return mclk;
}