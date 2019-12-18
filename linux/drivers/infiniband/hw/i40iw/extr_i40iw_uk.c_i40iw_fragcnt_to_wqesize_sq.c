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
 int I40IW_ERR_INVALID_FRAG_COUNT ; 
 int I40IW_QP_WQE_MIN_SIZE ; 

enum i40iw_status_code i40iw_fragcnt_to_wqesize_sq(u32 frag_cnt, u8 *wqe_size)
{
	switch (frag_cnt) {
	case 0:
	case 1:
		*wqe_size = I40IW_QP_WQE_MIN_SIZE;
		break;
	case 2:
	case 3:
		*wqe_size = 64;
		break;
	case 4:
	case 5:
		*wqe_size = 96;
		break;
	case 6:
	case 7:
		*wqe_size = 128;
		break;
	default:
		return I40IW_ERR_INVALID_FRAG_COUNT;
	}

	return 0;
}