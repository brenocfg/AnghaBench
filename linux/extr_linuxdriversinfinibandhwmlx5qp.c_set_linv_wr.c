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
struct mlx5_wqe_umr_ctrl_seg {int dummy; } ;
struct mlx5_mkey_seg {int dummy; } ;
struct TYPE_2__ {void* qend; } ;
struct mlx5_ib_qp {TYPE_1__ sq; } ;

/* Variables and functions */
 void* mlx5_get_send_wqe (struct mlx5_ib_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_linv_mkey_seg (void*) ; 
 int /*<<< orphan*/  set_linv_umr_seg (void*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void set_linv_wr(struct mlx5_ib_qp *qp, void **seg, int *size)
{
	set_linv_umr_seg(*seg);
	*seg += sizeof(struct mlx5_wqe_umr_ctrl_seg);
	*size += sizeof(struct mlx5_wqe_umr_ctrl_seg) / 16;
	if (unlikely((*seg == qp->sq.qend)))
		*seg = mlx5_get_send_wqe(qp, 0);
	set_linv_mkey_seg(*seg);
	*seg += sizeof(struct mlx5_mkey_seg);
	*size += sizeof(struct mlx5_mkey_seg) / 16;
	if (unlikely((*seg == qp->sq.qend)))
		*seg = mlx5_get_send_wqe(qp, 0);
}