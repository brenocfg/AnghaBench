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
#define  IB_VL_VL0 132 
#define  IB_VL_VL0_1 131 
#define  IB_VL_VL0_14 130 
#define  IB_VL_VL0_3 129 
#define  IB_VL_VL0_7 128 

__attribute__((used)) static inline int qib_num_vls(int vls)
{
	switch (vls) {
	default:
	case IB_VL_VL0:
		return 1;
	case IB_VL_VL0_1:
		return 2;
	case IB_VL_VL0_3:
		return 4;
	case IB_VL_VL0_7:
		return 8;
	case IB_VL_VL0_14:
		return 15;
	}
}