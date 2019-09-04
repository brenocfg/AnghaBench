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
struct TYPE_2__ {void* qend; } ;
struct mlx5_ib_qp {TYPE_1__ sq; } ;
struct mlx5_ib_mr {void* descs; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 void* mlx5_get_send_wqe (struct mlx5_ib_qp*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void set_reg_umr_inline_seg(void *seg, struct mlx5_ib_qp *qp,
				   struct mlx5_ib_mr *mr, int mr_list_size)
{
	void *qend = qp->sq.qend;
	void *addr = mr->descs;
	int copy;

	if (unlikely(seg + mr_list_size > qend)) {
		copy = qend - seg;
		memcpy(seg, addr, copy);
		addr += copy;
		mr_list_size -= copy;
		seg = mlx5_get_send_wqe(qp, 0);
	}
	memcpy(seg, addr, mr_list_size);
	seg += mr_list_size;
}