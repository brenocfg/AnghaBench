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
typedef  enum ib_wq_state { ____Placeholder_ib_wq_state } ib_wq_state ;

/* Variables and functions */
 int IB_QPS_ERR ; 
 int IB_QPS_RESET ; 
 int IB_QPS_RTR ; 
#define  IB_WQS_RDY 129 
#define  IB_WQS_RESET 128 

__attribute__((used)) static int ib_wq2qp_state(enum ib_wq_state state)
{
	switch (state) {
	case IB_WQS_RESET:
		return IB_QPS_RESET;
	case IB_WQS_RDY:
		return IB_QPS_RTR;
	default:
		return IB_QPS_ERR;
	}
}