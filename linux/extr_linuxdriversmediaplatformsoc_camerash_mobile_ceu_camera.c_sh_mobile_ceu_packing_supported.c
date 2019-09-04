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
struct soc_mbus_pixelfmt {scalar_t__ packing; int bits_per_sample; } ;

/* Variables and functions */
 scalar_t__ SOC_MBUS_PACKING_1_5X8 ; 
 scalar_t__ SOC_MBUS_PACKING_2X8_PADHI ; 
 scalar_t__ SOC_MBUS_PACKING_EXTEND16 ; 
 scalar_t__ SOC_MBUS_PACKING_NONE ; 

__attribute__((used)) static bool sh_mobile_ceu_packing_supported(const struct soc_mbus_pixelfmt *fmt)
{
	return	fmt->packing == SOC_MBUS_PACKING_NONE ||
		(fmt->bits_per_sample == 8 &&
		 fmt->packing == SOC_MBUS_PACKING_1_5X8) ||
		(fmt->bits_per_sample == 8 &&
		 fmt->packing == SOC_MBUS_PACKING_2X8_PADHI) ||
		(fmt->bits_per_sample > 8 &&
		 fmt->packing == SOC_MBUS_PACKING_EXTEND16);
}