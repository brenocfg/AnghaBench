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
typedef  enum qe_clock { ____Placeholder_qe_clock } qe_clock ;

/* Variables and functions */
 int EINVAL ; 
#define  QE_BRG12 135 
#define  QE_BRG13 134 
#define  QE_BRG3 133 
#define  QE_BRG4 132 
#define  QE_CLK1 131 
#define  QE_CLK2 130 
#define  QE_CLK23 129 
#define  QE_CLK24 128 

__attribute__((used)) static int ucc_get_tdm_common_clk(u32 tdm_num, enum qe_clock clock)
{
	int clock_bits = -EINVAL;

	/*
	 * for TDM[0, 1, 2, 3], TX and RX use  common
	 * clock source BRG3,4 and CLK1,2
	 * for TDM[4, 5, 6, 7], TX and RX use  common
	 * clock source BRG12,13 and CLK23,24
	 */
	switch (tdm_num) {
	case 0:
	case 1:
	case 2:
	case 3:
		switch (clock) {
		case QE_BRG3:
			clock_bits = 1;
			break;
		case QE_BRG4:
			clock_bits = 2;
			break;
		case QE_CLK1:
			clock_bits = 4;
			break;
		case QE_CLK2:
			clock_bits = 5;
			break;
		default:
			break;
		}
		break;
	case 4:
	case 5:
	case 6:
	case 7:
		switch (clock) {
		case QE_BRG12:
			clock_bits = 1;
			break;
		case QE_BRG13:
			clock_bits = 2;
			break;
		case QE_CLK23:
			clock_bits = 4;
			break;
		case QE_CLK24:
			clock_bits = 5;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return clock_bits;
}