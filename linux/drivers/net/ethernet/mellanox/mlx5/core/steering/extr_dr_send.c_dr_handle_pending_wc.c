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
struct mlx5dr_send_ring {scalar_t__ pending_wqe; scalar_t__ signal_th; int /*<<< orphan*/  cq; } ;
struct mlx5dr_domain {TYPE_1__* send_ring; } ;
struct TYPE_2__ {int signal_th; } ;

/* Variables and functions */
 int TH_NUMS_TO_DRAIN ; 
 int dr_poll_cq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dr_handle_pending_wc(struct mlx5dr_domain *dmn,
				struct mlx5dr_send_ring *send_ring)
{
	bool is_drain = false;
	int ne;

	if (send_ring->pending_wqe < send_ring->signal_th)
		return 0;

	/* Queue is full start drain it */
	if (send_ring->pending_wqe >=
	    dmn->send_ring->signal_th * TH_NUMS_TO_DRAIN)
		is_drain = true;

	do {
		ne = dr_poll_cq(send_ring->cq, 1);
		if (ne < 0)
			return ne;
		else if (ne == 1)
			send_ring->pending_wqe -= send_ring->signal_th;
	} while (is_drain && send_ring->pending_wqe);

	return 0;
}