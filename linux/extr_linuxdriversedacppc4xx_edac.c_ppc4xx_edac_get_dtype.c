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
typedef  enum dev_type { ____Placeholder_dev_type } dev_type ;

/* Variables and functions */
 int DEV_UNKNOWN ; 
 int DEV_X2 ; 
 int DEV_X4 ; 
#define  SDRAM_MCOPT1_WDTH_16 129 
#define  SDRAM_MCOPT1_WDTH_32 128 
 int SDRAM_MCOPT1_WDTH_MASK ; 

__attribute__((used)) static enum dev_type ppc4xx_edac_get_dtype(u32 mcopt1)
{
	switch (mcopt1 & SDRAM_MCOPT1_WDTH_MASK) {
	case SDRAM_MCOPT1_WDTH_16:
		return DEV_X2;
	case SDRAM_MCOPT1_WDTH_32:
		return DEV_X4;
	default:
		return DEV_UNKNOWN;
	}
}