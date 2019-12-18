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

/* Variables and functions */
 int AUX_CH_CTL ; 
 int AUX_CH_DATA1 ; 
 int AUX_CH_DATA2 ; 
 int AUX_CH_DATA3 ; 
 int AUX_CH_DATA4 ; 
 int AUX_CH_DATA5 ; 

__attribute__((used)) static inline int get_aux_ch_reg(unsigned int offset)
{
	int reg;

	switch (offset & 0xff) {
	case 0x10:
		reg = AUX_CH_CTL;
		break;
	case 0x14:
		reg = AUX_CH_DATA1;
		break;
	case 0x18:
		reg = AUX_CH_DATA2;
		break;
	case 0x1c:
		reg = AUX_CH_DATA3;
		break;
	case 0x20:
		reg = AUX_CH_DATA4;
		break;
	case 0x24:
		reg = AUX_CH_DATA5;
		break;
	default:
		reg = -1;
		break;
	}
	return reg;
}