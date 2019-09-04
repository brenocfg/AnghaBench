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
struct rxe_qp {int dummy; } ;
struct rxe_pkt_info {int dummy; } ;
typedef  enum resp_states { ____Placeholder_resp_states } resp_states ;

/* Variables and functions */
#define  IB_QPT_RC 129 
#define  IB_QPT_UC 128 
 int RESPST_CHK_RKEY ; 
 int qp_type (struct rxe_qp*) ; 

__attribute__((used)) static enum resp_states check_length(struct rxe_qp *qp,
				     struct rxe_pkt_info *pkt)
{
	switch (qp_type(qp)) {
	case IB_QPT_RC:
		return RESPST_CHK_RKEY;

	case IB_QPT_UC:
		return RESPST_CHK_RKEY;

	default:
		return RESPST_CHK_RKEY;
	}
}