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

/* Variables and functions */
 int IB_QPS_ERR ; 
 int IB_QPS_RESET ; 
 int IB_QPS_RTS ; 
 int IB_QPS_SQD ; 
 int IB_QPS_SQE ; 

__attribute__((used)) static inline bool hns_roce_v2_check_qp_stat(enum ib_qp_state cur_state,
					     enum ib_qp_state new_state)
{

	if ((cur_state != IB_QPS_RESET &&
	    (new_state == IB_QPS_ERR || new_state == IB_QPS_RESET)) ||
	    ((cur_state == IB_QPS_RTS || cur_state == IB_QPS_SQD) &&
	    (new_state == IB_QPS_RTS || new_state == IB_QPS_SQD)) ||
	    (cur_state == IB_QPS_SQE && new_state == IB_QPS_RTS))
		return true;

	return false;

}