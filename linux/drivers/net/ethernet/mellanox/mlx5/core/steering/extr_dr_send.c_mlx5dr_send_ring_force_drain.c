#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {uintptr_t addr; int length; scalar_t__ lkey; } ;
struct postsend_info {uintptr_t remote_addr; int /*<<< orphan*/  rkey; TYPE_1__ write; } ;
struct mlx5dr_send_ring {int signal_th; TYPE_3__* sync_mr; } ;
struct mlx5dr_domain {struct mlx5dr_send_ring* send_ring; } ;
struct TYPE_5__ {int /*<<< orphan*/  key; } ;
struct TYPE_6__ {TYPE_2__ mkey; scalar_t__ addr; } ;

/* Variables and functions */
 int DR_STE_SIZE ; 
 int TH_NUMS_TO_DRAIN ; 
 int dr_handle_pending_wc (struct mlx5dr_domain*,struct mlx5dr_send_ring*) ; 
 int dr_postsend_icm_data (struct mlx5dr_domain*,struct postsend_info*) ; 

int mlx5dr_send_ring_force_drain(struct mlx5dr_domain *dmn)
{
	struct mlx5dr_send_ring *send_ring = dmn->send_ring;
	struct postsend_info send_info = {};
	u8 data[DR_STE_SIZE];
	int num_of_sends_req;
	int ret;
	int i;

	/* Sending this amount of requests makes sure we will get drain */
	num_of_sends_req = send_ring->signal_th * TH_NUMS_TO_DRAIN / 2;

	/* Send fake requests forcing the last to be signaled */
	send_info.write.addr = (uintptr_t)data;
	send_info.write.length = DR_STE_SIZE;
	send_info.write.lkey = 0;
	/* Using the sync_mr in order to write/read */
	send_info.remote_addr = (uintptr_t)send_ring->sync_mr->addr;
	send_info.rkey = send_ring->sync_mr->mkey.key;

	for (i = 0; i < num_of_sends_req; i++) {
		ret = dr_postsend_icm_data(dmn, &send_info);
		if (ret)
			return ret;
	}

	ret = dr_handle_pending_wc(dmn, send_ring);

	return ret;
}