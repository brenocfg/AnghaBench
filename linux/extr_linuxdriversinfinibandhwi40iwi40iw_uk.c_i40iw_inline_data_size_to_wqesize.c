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
typedef  int u32 ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int I40IW_ERR_INVALID_INLINE_DATA_SIZE ; 
 int I40IW_MAX_INLINE_DATA_SIZE ; 
 int I40IW_QP_WQE_MIN_SIZE ; 

enum i40iw_status_code i40iw_inline_data_size_to_wqesize(u32 data_size,
							 u8 *wqe_size)
{
	if (data_size > I40IW_MAX_INLINE_DATA_SIZE)
		return I40IW_ERR_INVALID_INLINE_DATA_SIZE;

	if (data_size <= 16)
		*wqe_size = I40IW_QP_WQE_MIN_SIZE;
	else
		*wqe_size = 64;

	return 0;
}