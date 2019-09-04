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
#define  IB_SPEED_DDR 133 
#define  IB_SPEED_EDR 132 
#define  IB_SPEED_FDR 131 
#define  IB_SPEED_FDR10 130 
#define  IB_SPEED_QDR 129 
#define  IB_SPEED_SDR 128 
 int SPEED_10000 ; 
 int SPEED_14000 ; 
 int SPEED_2500 ; 
 int SPEED_25000 ; 
 int SPEED_5000 ; 
 int SPEED_UNKNOWN ; 

__attribute__((used)) static inline int ib_speed_enum_to_int(int speed)
{
	switch (speed) {
	case IB_SPEED_SDR:
		return SPEED_2500;
	case IB_SPEED_DDR:
		return SPEED_5000;
	case IB_SPEED_QDR:
	case IB_SPEED_FDR10:
		return SPEED_10000;
	case IB_SPEED_FDR:
		return SPEED_14000;
	case IB_SPEED_EDR:
		return SPEED_25000;
	}

	return SPEED_UNKNOWN;
}