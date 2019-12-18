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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_fpga_tls {int /*<<< orphan*/  rx_idr_spinlock; int /*<<< orphan*/  rx_idr; int /*<<< orphan*/  tx_idr_spinlock; int /*<<< orphan*/  tx_idr; } ;
struct mlx5_core_dev {TYPE_1__* fpga; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {struct mlx5_fpga_tls* tls; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_fpga_err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 void* mlx5_fpga_tls_release_swid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fpga_tls_send_teardown_cmd (struct mlx5_core_dev*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void mlx5_fpga_tls_del_flow(struct mlx5_core_dev *mdev, u32 swid,
			    gfp_t flags, bool direction_sx)
{
	struct mlx5_fpga_tls *tls = mdev->fpga->tls;
	void *flow;

	if (direction_sx)
		flow = mlx5_fpga_tls_release_swid(&tls->tx_idr,
						  &tls->tx_idr_spinlock,
						  swid);
	else
		flow = mlx5_fpga_tls_release_swid(&tls->rx_idr,
						  &tls->rx_idr_spinlock,
						  swid);

	if (!flow) {
		mlx5_fpga_err(mdev->fpga, "No flow information for swid %u\n",
			      swid);
		return;
	}

	synchronize_rcu(); /* before kfree(flow) */
	mlx5_fpga_tls_send_teardown_cmd(mdev, flow, swid, flags);
}