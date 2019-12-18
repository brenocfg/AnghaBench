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
struct m88rs2000_state {int dummy; } ;
typedef  enum fe_code_rate { ____Placeholder_fe_code_rate } fe_code_rate ;

/* Variables and functions */
 int FEC_1_2 ; 
 int FEC_2_3 ; 
 int FEC_3_4 ; 
 int FEC_5_6 ; 
 int FEC_7_8 ; 
 int FEC_AUTO ; 
 int m88rs2000_readreg (struct m88rs2000_state*,int) ; 
 int /*<<< orphan*/  m88rs2000_writereg (struct m88rs2000_state*,int,int) ; 

__attribute__((used)) static enum fe_code_rate m88rs2000_get_fec(struct m88rs2000_state *state)
{
	u8 reg;
	m88rs2000_writereg(state, 0x9a, 0x30);
	reg = m88rs2000_readreg(state, 0x76);
	m88rs2000_writereg(state, 0x9a, 0xb0);

	reg &= 0xf0;
	reg >>= 5;

	switch (reg) {
	case 0x4:
		return FEC_1_2;
	case 0x3:
		return FEC_2_3;
	case 0x2:
		return FEC_3_4;
	case 0x1:
		return FEC_5_6;
	case 0x0:
		return FEC_7_8;
	default:
		break;
	}

	return FEC_AUTO;
}