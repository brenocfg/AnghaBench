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
typedef  enum ib_qp_state { ____Placeholder_ib_qp_state } ib_qp_state ;
typedef  enum ib_qp_attr_mask { ____Placeholder_ib_qp_attr_mask } ib_qp_attr_mask ;

/* Variables and functions */
 int IB_QPS_ERR ; 
 int IB_QPS_INIT ; 
 int IB_QPS_RESET ; 
 int IB_QPS_RTR ; 
 int IB_QPS_RTS ; 
 int IB_QP_AV ; 
 int IB_QP_MAX_QP_RD_ATOMIC ; 
 int IB_QP_MIN_RNR_TIMER ; 
 int IB_QP_PATH_MTU ; 
 int IB_QP_PKEY_INDEX ; 
 int IB_QP_PORT ; 
 int IB_QP_RETRY_CNT ; 
 int IB_QP_RNR_RETRY ; 
 int IB_QP_SQ_PSN ; 
 int IB_QP_STATE ; 
 int IB_QP_TIMEOUT ; 
 int is_valid_mask (int,int,int) ; 

__attribute__((used)) static bool modify_dci_qp_is_ok(enum ib_qp_state cur_state, enum ib_qp_state new_state,
				enum ib_qp_attr_mask attr_mask)
{
	int req = IB_QP_STATE;
	int opt = 0;

	if (new_state == IB_QPS_RESET) {
		return is_valid_mask(attr_mask, req, opt);
	} else if (cur_state == IB_QPS_RESET && new_state == IB_QPS_INIT) {
		req |= IB_QP_PKEY_INDEX | IB_QP_PORT;
		return is_valid_mask(attr_mask, req, opt);
	} else if (cur_state == IB_QPS_INIT && new_state == IB_QPS_INIT) {
		opt = IB_QP_PKEY_INDEX | IB_QP_PORT;
		return is_valid_mask(attr_mask, req, opt);
	} else if (cur_state == IB_QPS_INIT && new_state == IB_QPS_RTR) {
		req |= IB_QP_PATH_MTU;
		opt = IB_QP_PKEY_INDEX | IB_QP_AV;
		return is_valid_mask(attr_mask, req, opt);
	} else if (cur_state == IB_QPS_RTR && new_state == IB_QPS_RTS) {
		req |= IB_QP_TIMEOUT | IB_QP_RETRY_CNT | IB_QP_RNR_RETRY |
		       IB_QP_MAX_QP_RD_ATOMIC | IB_QP_SQ_PSN;
		opt = IB_QP_MIN_RNR_TIMER;
		return is_valid_mask(attr_mask, req, opt);
	} else if (cur_state == IB_QPS_RTS && new_state == IB_QPS_RTS) {
		opt = IB_QP_MIN_RNR_TIMER;
		return is_valid_mask(attr_mask, req, opt);
	} else if (cur_state != IB_QPS_RESET && new_state == IB_QPS_ERR) {
		return is_valid_mask(attr_mask, req, opt);
	}
	return false;
}