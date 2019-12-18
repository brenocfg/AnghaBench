#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int fence_size; } ;
struct mlx4_wqe_ctrl_seg {TYPE_2__ qpn_vlan; } ;
struct TYPE_3__ {int wqe_cnt; } ;
struct mlx4_ib_qp {TYPE_1__ sq; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 void* get_send_wqe (struct mlx4_ib_qp*,int) ; 

__attribute__((used)) static void stamp_send_wqe(struct mlx4_ib_qp *qp, int n)
{
	__be32 *wqe;
	int i;
	int s;
	void *buf;
	struct mlx4_wqe_ctrl_seg *ctrl;

	buf = get_send_wqe(qp, n & (qp->sq.wqe_cnt - 1));
	ctrl = (struct mlx4_wqe_ctrl_seg *)buf;
	s = (ctrl->qpn_vlan.fence_size & 0x3f) << 4;
	for (i = 64; i < s; i += 64) {
		wqe = buf + i;
		*wqe = cpu_to_be32(0xffffffff);
	}
}