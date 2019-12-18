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
typedef  enum motionsensor_type { ____Placeholder_motionsensor_type } motionsensor_type ;

/* Variables and functions */
#define  MOTIONSENSE_TYPE_ACCEL 134 
#define  MOTIONSENSE_TYPE_ACTIVITY 133 
#define  MOTIONSENSE_TYPE_BARO 132 
#define  MOTIONSENSE_TYPE_GYRO 131 
#define  MOTIONSENSE_TYPE_LIGHT 130 
#define  MOTIONSENSE_TYPE_MAG 129 
#define  MOTIONSENSE_TYPE_PROX 128 

__attribute__((used)) static void get_default_min_max_freq(enum motionsensor_type type,
				     u32 *min_freq,
				     u32 *max_freq)
{
	switch (type) {
	case MOTIONSENSE_TYPE_ACCEL:
	case MOTIONSENSE_TYPE_GYRO:
		*min_freq = 12500;
		*max_freq = 100000;
		break;
	case MOTIONSENSE_TYPE_MAG:
		*min_freq = 5000;
		*max_freq = 25000;
		break;
	case MOTIONSENSE_TYPE_PROX:
	case MOTIONSENSE_TYPE_LIGHT:
		*min_freq = 100;
		*max_freq = 50000;
		break;
	case MOTIONSENSE_TYPE_BARO:
		*min_freq = 250;
		*max_freq = 20000;
		break;
	case MOTIONSENSE_TYPE_ACTIVITY:
	default:
		*min_freq = 0;
		*max_freq = 0;
		break;
	}
}