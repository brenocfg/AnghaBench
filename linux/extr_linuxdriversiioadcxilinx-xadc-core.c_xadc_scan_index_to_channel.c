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
 unsigned int XADC_REG_TEMP ; 
 unsigned int XADC_REG_VAUX (unsigned int) ; 
 unsigned int XADC_REG_VCCAUX ; 
 unsigned int XADC_REG_VCCBRAM ; 
 unsigned int XADC_REG_VCCINT ; 
 unsigned int XADC_REG_VCCO_DDR ; 
 unsigned int XADC_REG_VCCPAUX ; 
 unsigned int XADC_REG_VCCPINT ; 
 unsigned int XADC_REG_VPVN ; 
 unsigned int XADC_REG_VREFN ; 
 unsigned int XADC_REG_VREFP ; 

__attribute__((used)) static unsigned int xadc_scan_index_to_channel(unsigned int scan_index)
{
	switch (scan_index) {
	case 5:
		return XADC_REG_VCCPINT;
	case 6:
		return XADC_REG_VCCPAUX;
	case 7:
		return XADC_REG_VCCO_DDR;
	case 8:
		return XADC_REG_TEMP;
	case 9:
		return XADC_REG_VCCINT;
	case 10:
		return XADC_REG_VCCAUX;
	case 11:
		return XADC_REG_VPVN;
	case 12:
		return XADC_REG_VREFP;
	case 13:
		return XADC_REG_VREFN;
	case 14:
		return XADC_REG_VCCBRAM;
	default:
		return XADC_REG_VAUX(scan_index - 16);
	}
}