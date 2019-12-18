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
typedef  int u32 ;
struct tls_crypto_info {int dummy; } ;
struct mlx5_fpga_tls {int /*<<< orphan*/  rx_idr_spinlock; int /*<<< orphan*/  rx_idr; int /*<<< orphan*/  tx_idr_spinlock; int /*<<< orphan*/  tx_idr; } ;
struct mlx5_core_dev {TYPE_1__* fpga; } ;
struct TYPE_2__ {struct mlx5_fpga_tls* tls; } ;

/* Variables and functions */
 int EINTR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int,int) ; 
 int _mlx5_fpga_tls_add_flow (struct mlx5_core_dev*,void*,struct tls_crypto_info*,int,int) ; 
 int mlx5_fpga_tls_alloc_swid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  mlx5_fpga_tls_release_swid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tls_flow ; 

int mlx5_fpga_tls_add_flow(struct mlx5_core_dev *mdev, void *flow,
			   struct tls_crypto_info *crypto_info,
			   u32 start_offload_tcp_sn, u32 *p_swid,
			   bool direction_sx)
{
	struct mlx5_fpga_tls *tls = mdev->fpga->tls;
	int ret = -ENOMEM;
	u32 swid;

	if (direction_sx)
		ret = mlx5_fpga_tls_alloc_swid(&tls->tx_idr,
					       &tls->tx_idr_spinlock, flow);
	else
		ret = mlx5_fpga_tls_alloc_swid(&tls->rx_idr,
					       &tls->rx_idr_spinlock, flow);

	if (ret < 0)
		return ret;

	swid = ret;
	MLX5_SET(tls_flow, flow, direction_sx, direction_sx ? 1 : 0);

	ret = _mlx5_fpga_tls_add_flow(mdev, flow, crypto_info, swid,
				      start_offload_tcp_sn);
	if (ret && ret != -EINTR)
		goto free_swid;

	*p_swid = swid;
	return 0;
free_swid:
	if (direction_sx)
		mlx5_fpga_tls_release_swid(&tls->tx_idr,
					   &tls->tx_idr_spinlock, swid);
	else
		mlx5_fpga_tls_release_swid(&tls->rx_idr,
					   &tls->rx_idr_spinlock, swid);

	return ret;
}