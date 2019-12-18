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
typedef  int u8 ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MLX5_VL_HW_0 132 
#define  MLX5_VL_HW_0_1 131 
#define  MLX5_VL_HW_0_14 130 
#define  MLX5_VL_HW_0_3 129 
#define  MLX5_VL_HW_0_7 128 
 int __IB_MAX_VL_0 ; 
 int __IB_MAX_VL_0_1 ; 
 int __IB_MAX_VL_0_14 ; 
 int __IB_MAX_VL_0_3 ; 
 int __IB_MAX_VL_0_7 ; 

__attribute__((used)) static int translate_max_vl_num(struct ib_device *ibdev, u8 vl_hw_cap,
				u8 *max_vl_num)
{
	switch (vl_hw_cap) {
	case MLX5_VL_HW_0:
		*max_vl_num = __IB_MAX_VL_0;
		break;
	case MLX5_VL_HW_0_1:
		*max_vl_num = __IB_MAX_VL_0_1;
		break;
	case MLX5_VL_HW_0_3:
		*max_vl_num = __IB_MAX_VL_0_3;
		break;
	case MLX5_VL_HW_0_7:
		*max_vl_num = __IB_MAX_VL_0_7;
		break;
	case MLX5_VL_HW_0_14:
		*max_vl_num = __IB_MAX_VL_0_14;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}