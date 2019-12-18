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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  qpn; } ;
struct TYPE_4__ {TYPE_1__ mqp; } ;
struct mlx5_ib_sq {int /*<<< orphan*/  state; TYPE_2__ base; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int mlx5_core_query_sq_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_raw_packet_qp_sq_state(struct mlx5_ib_dev *dev,
					struct mlx5_ib_sq *sq,
					u8 *sq_state)
{
	int err;

	err = mlx5_core_query_sq_state(dev->mdev, sq->base.mqp.qpn, sq_state);
	if (err)
		goto out;
	sq->state = *sq_state;

out:
	return err;
}