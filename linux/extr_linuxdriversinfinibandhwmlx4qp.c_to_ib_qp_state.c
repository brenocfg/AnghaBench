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
typedef  enum mlx4_qp_state { ____Placeholder_mlx4_qp_state } mlx4_qp_state ;
typedef  enum ib_qp_state { ____Placeholder_ib_qp_state } ib_qp_state ;

/* Variables and functions */
 int IB_QPS_ERR ; 
 int IB_QPS_INIT ; 
 int IB_QPS_RESET ; 
 int IB_QPS_RTR ; 
 int IB_QPS_RTS ; 
 int IB_QPS_SQD ; 
 int IB_QPS_SQE ; 
#define  MLX4_QP_STATE_ERR 135 
#define  MLX4_QP_STATE_INIT 134 
#define  MLX4_QP_STATE_RST 133 
#define  MLX4_QP_STATE_RTR 132 
#define  MLX4_QP_STATE_RTS 131 
#define  MLX4_QP_STATE_SQD 130 
#define  MLX4_QP_STATE_SQER 129 
#define  MLX4_QP_STATE_SQ_DRAINING 128 

__attribute__((used)) static inline enum ib_qp_state to_ib_qp_state(enum mlx4_qp_state mlx4_state)
{
	switch (mlx4_state) {
	case MLX4_QP_STATE_RST:      return IB_QPS_RESET;
	case MLX4_QP_STATE_INIT:     return IB_QPS_INIT;
	case MLX4_QP_STATE_RTR:      return IB_QPS_RTR;
	case MLX4_QP_STATE_RTS:      return IB_QPS_RTS;
	case MLX4_QP_STATE_SQ_DRAINING:
	case MLX4_QP_STATE_SQD:      return IB_QPS_SQD;
	case MLX4_QP_STATE_SQER:     return IB_QPS_SQE;
	case MLX4_QP_STATE_ERR:      return IB_QPS_ERR;
	default:		     return -1;
	}
}