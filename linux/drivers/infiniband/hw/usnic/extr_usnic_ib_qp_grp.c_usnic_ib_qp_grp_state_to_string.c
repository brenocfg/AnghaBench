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
#define  IB_QPS_ERR 134 
#define  IB_QPS_INIT 133 
#define  IB_QPS_RESET 132 
#define  IB_QPS_RTR 131 
#define  IB_QPS_RTS 130 
#define  IB_QPS_SQD 129 
#define  IB_QPS_SQE 128 

const char *usnic_ib_qp_grp_state_to_string(enum ib_qp_state state)
{
	switch (state) {
	case IB_QPS_RESET:
		return "Rst";
	case IB_QPS_INIT:
		return "Init";
	case IB_QPS_RTR:
		return "RTR";
	case IB_QPS_RTS:
		return "RTS";
	case IB_QPS_SQD:
		return "SQD";
	case IB_QPS_SQE:
		return "SQE";
	case IB_QPS_ERR:
		return "ERR";
	default:
		return "UNKNOWN STATE";

	}
}