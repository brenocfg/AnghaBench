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
typedef  enum dev_sku_info { ____Placeholder_dev_sku_info } dev_sku_info ;

/* Variables and functions */
#define  DEV_SKU_1 133 
#define  DEV_SKU_2 132 
#define  DEV_SKU_3 131 
#define  DEV_SKU_4 130 
#define  DEV_SKU_UNKNOWN 129 
#define  DEV_SKU_VF 128 

__attribute__((used)) static inline const char *get_sku_info(enum dev_sku_info info)
{
	switch (info) {
	case DEV_SKU_1:
		return "SKU1";
	case DEV_SKU_2:
		return "SKU2";
	case DEV_SKU_3:
		return "SKU3";
	case DEV_SKU_4:
		return "SKU4";
	case DEV_SKU_VF:
		return "SKUVF";
	case DEV_SKU_UNKNOWN:
	default:
		break;
	}
	return "Unknown SKU";
}