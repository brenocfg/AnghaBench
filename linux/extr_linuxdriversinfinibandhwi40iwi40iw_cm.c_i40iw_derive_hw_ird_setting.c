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
typedef  scalar_t__ u16 ;

/* Variables and functions */
#define  I40IW_HW_IRD_SETTING_16 133 
#define  I40IW_HW_IRD_SETTING_2 132 
#define  I40IW_HW_IRD_SETTING_32 131 
#define  I40IW_HW_IRD_SETTING_4 130 
#define  I40IW_HW_IRD_SETTING_64 129 
#define  I40IW_HW_IRD_SETTING_8 128 
 int roundup_pow_of_two (scalar_t__) ; 

__attribute__((used)) static u8 i40iw_derive_hw_ird_setting(u16 cm_ird)
{
	u8 encoded_ird_size;

	/* ird_size field is encoded in qp_ctx */
	switch (cm_ird ? roundup_pow_of_two(cm_ird) : 0) {
	case I40IW_HW_IRD_SETTING_64:
		encoded_ird_size = 3;
		break;
	case I40IW_HW_IRD_SETTING_32:
	case I40IW_HW_IRD_SETTING_16:
		encoded_ird_size = 2;
		break;
	case I40IW_HW_IRD_SETTING_8:
	case I40IW_HW_IRD_SETTING_4:
		encoded_ird_size = 1;
		break;
	case I40IW_HW_IRD_SETTING_2:
	default:
		encoded_ird_size = 0;
		break;
	}
	return encoded_ird_size;
}