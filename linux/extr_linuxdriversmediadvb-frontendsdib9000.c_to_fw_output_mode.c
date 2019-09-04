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
typedef  int u16 ;

/* Variables and functions */
#define  OUTMODE_ANALOG_ADC 134 
#define  OUTMODE_DIVERSITY 133 
#define  OUTMODE_HIGH_Z 132 
#define  OUTMODE_MPEG2_FIFO 131 
#define  OUTMODE_MPEG2_PAR_CONT_CLK 130 
#define  OUTMODE_MPEG2_PAR_GATED_CLK 129 
#define  OUTMODE_MPEG2_SERIAL 128 

__attribute__((used)) static u16 to_fw_output_mode(u16 mode)
{
	switch (mode) {
	case OUTMODE_HIGH_Z:
		return 0;
	case OUTMODE_MPEG2_PAR_GATED_CLK:
		return 4;
	case OUTMODE_MPEG2_PAR_CONT_CLK:
		return 8;
	case OUTMODE_MPEG2_SERIAL:
		return 16;
	case OUTMODE_DIVERSITY:
		return 128;
	case OUTMODE_MPEG2_FIFO:
		return 2;
	case OUTMODE_ANALOG_ADC:
		return 1;
	default:
		return 0;
	}
}