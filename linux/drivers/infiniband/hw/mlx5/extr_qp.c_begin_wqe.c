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
struct mlx5_wqe_ctrl_seg {int dummy; } ;
struct mlx5_ib_qp {int dummy; } ;
struct ib_send_wr {int send_flags; } ;

/* Variables and functions */
 int IB_SEND_SIGNALED ; 
 int IB_SEND_SOLICITED ; 
 int __begin_wqe (struct mlx5_ib_qp*,void**,struct mlx5_wqe_ctrl_seg**,struct ib_send_wr const*,unsigned int*,int*,void**,int,int,int) ; 

__attribute__((used)) static int begin_wqe(struct mlx5_ib_qp *qp, void **seg,
		     struct mlx5_wqe_ctrl_seg **ctrl,
		     const struct ib_send_wr *wr, unsigned *idx,
		     int *size, void **cur_edge, int nreq)
{
	return __begin_wqe(qp, seg, ctrl, wr, idx, size, cur_edge, nreq,
			   wr->send_flags & IB_SEND_SIGNALED,
			   wr->send_flags & IB_SEND_SOLICITED);
}