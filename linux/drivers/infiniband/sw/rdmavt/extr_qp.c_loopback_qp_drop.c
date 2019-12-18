#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ qp_type; } ;
struct rvt_qp {TYPE_1__ ibqp; } ;
struct rvt_ibport {int /*<<< orphan*/  n_pkt_drops; } ;
typedef  enum ib_wc_status { ____Placeholder_ib_wc_status } ib_wc_status ;

/* Variables and functions */
 scalar_t__ IB_QPT_RC ; 
 int IB_WC_RETRY_EXC_ERR ; 
 int IB_WC_SUCCESS ; 

__attribute__((used)) static enum ib_wc_status loopback_qp_drop(struct rvt_ibport *rvp,
					  struct rvt_qp *sqp)
{
	rvp->n_pkt_drops++;
	/*
	 * For RC, the requester would timeout and retry so
	 * shortcut the timeouts and just signal too many retries.
	 */
	return sqp->ibqp.qp_type == IB_QPT_RC ?
		IB_WC_RETRY_EXC_ERR : IB_WC_SUCCESS;
}