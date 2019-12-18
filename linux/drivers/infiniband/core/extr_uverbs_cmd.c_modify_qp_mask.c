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
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;

/* Variables and functions */
#define  IB_QPT_XRC_INI 129 
#define  IB_QPT_XRC_TGT 128 
 int IB_QP_MAX_DEST_RD_ATOMIC ; 
 int IB_QP_MAX_QP_RD_ATOMIC ; 
 int IB_QP_MIN_RNR_TIMER ; 
 int IB_QP_RETRY_CNT ; 
 int IB_QP_RNR_RETRY ; 

__attribute__((used)) static int modify_qp_mask(enum ib_qp_type qp_type, int mask)
{
	switch (qp_type) {
	case IB_QPT_XRC_INI:
		return mask & ~(IB_QP_MAX_DEST_RD_ATOMIC | IB_QP_MIN_RNR_TIMER);
	case IB_QPT_XRC_TGT:
		return mask & ~(IB_QP_MAX_QP_RD_ATOMIC | IB_QP_RETRY_CNT |
				IB_QP_RNR_RETRY);
	default:
		return mask;
	}
}