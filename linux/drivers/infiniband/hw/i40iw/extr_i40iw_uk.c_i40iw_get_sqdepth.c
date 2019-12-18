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
 int I40IW_ERR_INVALID_SIZE ; 
 int I40IW_QP_SW_MAX_SQ_QUANTAS ; 
 int I40IW_QP_SW_MIN_WQSIZE ; 
 scalar_t__ I40IW_SQ_RSVD ; 
 int roundup_pow_of_two (scalar_t__) ; 

enum i40iw_status_code i40iw_get_sqdepth(u32 sq_size, u8 shift, u32 *sqdepth)
{
	*sqdepth = roundup_pow_of_two((sq_size << shift) + I40IW_SQ_RSVD);

	if (*sqdepth < (I40IW_QP_SW_MIN_WQSIZE << shift))
		*sqdepth = I40IW_QP_SW_MIN_WQSIZE << shift;
	else if (*sqdepth > I40IW_QP_SW_MAX_SQ_QUANTAS)
		return I40IW_ERR_INVALID_SIZE;

	return 0;
}