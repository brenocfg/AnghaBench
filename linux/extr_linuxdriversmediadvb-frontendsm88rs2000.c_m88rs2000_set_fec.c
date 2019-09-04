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
#define  FEC_1_2 133 
#define  FEC_2_3 132 
#define  FEC_3_4 131 
#define  FEC_5_6 130 
#define  FEC_7_8 129 
#define  FEC_AUTO 128 
 int m88rs2000_readreg (struct m88rs2000_state*,int) ; 
 int m88rs2000_writereg (struct m88rs2000_state*,int,int) ; 

__attribute__((used)) static int m88rs2000_set_fec(struct m88rs2000_state *state,
			     enum fe_code_rate fec)
{
	u8 fec_set, reg;
	int ret;

	switch (fec) {
	case FEC_1_2:
		fec_set = 0x8;
		break;
	case FEC_2_3:
		fec_set = 0x10;
		break;
	case FEC_3_4:
		fec_set = 0x20;
		break;
	case FEC_5_6:
		fec_set = 0x40;
		break;
	case FEC_7_8:
		fec_set = 0x80;
		break;
	case FEC_AUTO:
	default:
		fec_set = 0x0;
	}

	reg = m88rs2000_readreg(state, 0x70);
	reg &= 0x7;
	ret = m88rs2000_writereg(state, 0x70, reg | fec_set);

	ret |= m88rs2000_writereg(state, 0x76, 0x8);

	return ret;
}