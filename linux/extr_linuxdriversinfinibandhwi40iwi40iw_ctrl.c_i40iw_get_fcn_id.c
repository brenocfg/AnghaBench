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
typedef  size_t u8 ;
struct i40iw_sc_dev {int* fcn_id_array; } ;

/* Variables and functions */
 size_t I40IW_FIRST_NON_PF_STAT ; 
 size_t I40IW_INVALID_FCN_ID ; 
 size_t I40IW_MAX_STATS_COUNT ; 

__attribute__((used)) static u8 i40iw_get_fcn_id(struct i40iw_sc_dev *dev)
{
	u8 fcn_id = I40IW_INVALID_FCN_ID;
	u8 i;

	for (i = I40IW_FIRST_NON_PF_STAT; i < I40IW_MAX_STATS_COUNT; i++)
		if (!dev->fcn_id_array[i]) {
			fcn_id = i;
			dev->fcn_id_array[i] = true;
			break;
		}
	return fcn_id;
}