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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ib_qp_attr {unsigned long long timeout; int retry_cnt; } ;

/* Variables and functions */
 int IB_QP_RETRY_CNT ; 
 int IB_QP_TIMEOUT ; 
 int /*<<< orphan*/  NSEC_PER_MSEC ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 

__attribute__((used)) static uint32_t srp_compute_rq_tmo(struct ib_qp_attr *qp_attr, int attr_mask)
{
	uint64_t T_tr_ns, max_compl_time_ms;
	uint32_t rq_tmo_jiffies;

	/*
	 * According to section 11.2.4.2 in the IBTA spec (Modify Queue Pair,
	 * table 91), both the QP timeout and the retry count have to be set
	 * for RC QP's during the RTR to RTS transition.
	 */
	WARN_ON_ONCE((attr_mask & (IB_QP_TIMEOUT | IB_QP_RETRY_CNT)) !=
		     (IB_QP_TIMEOUT | IB_QP_RETRY_CNT));

	/*
	 * Set target->rq_tmo_jiffies to one second more than the largest time
	 * it can take before an error completion is generated. See also
	 * C9-140..142 in the IBTA spec for more information about how to
	 * convert the QP Local ACK Timeout value to nanoseconds.
	 */
	T_tr_ns = 4096 * (1ULL << qp_attr->timeout);
	max_compl_time_ms = qp_attr->retry_cnt * 4 * T_tr_ns;
	do_div(max_compl_time_ms, NSEC_PER_MSEC);
	rq_tmo_jiffies = msecs_to_jiffies(max_compl_time_ms + 1000);

	return rq_tmo_jiffies;
}