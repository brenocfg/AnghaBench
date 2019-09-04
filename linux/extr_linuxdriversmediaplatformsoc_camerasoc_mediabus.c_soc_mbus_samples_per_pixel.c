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
struct soc_mbus_pixelfmt {int packing; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SOC_MBUS_PACKING_1_5X8 134 
#define  SOC_MBUS_PACKING_2X8_PADHI 133 
#define  SOC_MBUS_PACKING_2X8_PADLO 132 
#define  SOC_MBUS_PACKING_EXTEND16 131 
#define  SOC_MBUS_PACKING_EXTEND32 130 
#define  SOC_MBUS_PACKING_NONE 129 
#define  SOC_MBUS_PACKING_VARIABLE 128 

int soc_mbus_samples_per_pixel(const struct soc_mbus_pixelfmt *mf,
			unsigned int *numerator, unsigned int *denominator)
{
	switch (mf->packing) {
	case SOC_MBUS_PACKING_NONE:
	case SOC_MBUS_PACKING_EXTEND16:
		*numerator = 1;
		*denominator = 1;
		return 0;
	case SOC_MBUS_PACKING_EXTEND32:
		*numerator = 1;
		*denominator = 1;
		return 0;
	case SOC_MBUS_PACKING_2X8_PADHI:
	case SOC_MBUS_PACKING_2X8_PADLO:
		*numerator = 2;
		*denominator = 1;
		return 0;
	case SOC_MBUS_PACKING_1_5X8:
		*numerator = 3;
		*denominator = 2;
		return 0;
	case SOC_MBUS_PACKING_VARIABLE:
		*numerator = 0;
		*denominator = 1;
		return 0;
	}
	return -EINVAL;
}