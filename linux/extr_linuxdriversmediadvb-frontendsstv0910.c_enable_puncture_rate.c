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
struct stv {scalar_t__ regoff; } ;
typedef  enum fe_code_rate { ____Placeholder_fe_code_rate } fe_code_rate ;

/* Variables and functions */
#define  FEC_1_2 133 
#define  FEC_2_3 132 
#define  FEC_3_4 131 
#define  FEC_5_6 130 
#define  FEC_7_8 129 
#define  FEC_NONE 128 
 scalar_t__ RSTV0910_P2_PRVIT ; 
 int write_reg (struct stv*,scalar_t__,int) ; 

__attribute__((used)) static int enable_puncture_rate(struct stv *state, enum fe_code_rate rate)
{
	u8 val;

	switch (rate) {
	case FEC_1_2:
		val = 0x01;
		break;
	case FEC_2_3:
		val = 0x02;
		break;
	case FEC_3_4:
		val = 0x04;
		break;
	case FEC_5_6:
		val = 0x08;
		break;
	case FEC_7_8:
		val = 0x20;
		break;
	case FEC_NONE:
	default:
		val = 0x2f;
		break;
	}

	return write_reg(state, RSTV0910_P2_PRVIT + state->regoff, val);
}