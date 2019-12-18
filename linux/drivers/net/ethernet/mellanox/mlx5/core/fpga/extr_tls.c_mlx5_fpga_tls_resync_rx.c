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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_fpga_dma_buf {int /*<<< orphan*/  complete; TYPE_1__* sg; } ;
struct mlx5_core_dev {TYPE_3__* fpga; } ;
struct TYPE_6__ {TYPE_2__* tls; } ;
struct TYPE_5__ {int /*<<< orphan*/  conn; int /*<<< orphan*/  rx_idr; } ;
struct TYPE_4__ {int size; void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RESYNC_RX ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET64 (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_TLS_COMMAND_SIZE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  command_type ; 
 void* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_fpga_dma_buf*) ; 
 struct mlx5_fpga_dma_buf* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_fpga_sbu_conn_sendmsg (int /*<<< orphan*/ ,struct mlx5_fpga_dma_buf*) ; 
 int /*<<< orphan*/  mlx5_fpga_tls_flow_to_cmd (void*,void*) ; 
 int /*<<< orphan*/  mlx_tls_kfree_complete ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  swid ; 
 int /*<<< orphan*/  tcp_sn ; 
 int /*<<< orphan*/  tls_cmd ; 
 int /*<<< orphan*/  tls_rcd_sn ; 
 scalar_t__ unlikely (int) ; 

int mlx5_fpga_tls_resync_rx(struct mlx5_core_dev *mdev, u32 handle, u32 seq,
			    u64 rcd_sn)
{
	struct mlx5_fpga_dma_buf *buf;
	int size = sizeof(*buf) + MLX5_TLS_COMMAND_SIZE;
	void *flow;
	void *cmd;
	int ret;

	buf = kzalloc(size, GFP_ATOMIC);
	if (!buf)
		return -ENOMEM;

	cmd = (buf + 1);

	rcu_read_lock();
	flow = idr_find(&mdev->fpga->tls->rx_idr, ntohl(handle));
	if (unlikely(!flow)) {
		rcu_read_unlock();
		WARN_ONCE(1, "Received NULL pointer for handle\n");
		kfree(buf);
		return -EINVAL;
	}
	mlx5_fpga_tls_flow_to_cmd(flow, cmd);
	rcu_read_unlock();

	MLX5_SET(tls_cmd, cmd, swid, ntohl(handle));
	MLX5_SET64(tls_cmd, cmd, tls_rcd_sn, be64_to_cpu(rcd_sn));
	MLX5_SET(tls_cmd, cmd, tcp_sn, seq);
	MLX5_SET(tls_cmd, cmd, command_type, CMD_RESYNC_RX);

	buf->sg[0].data = cmd;
	buf->sg[0].size = MLX5_TLS_COMMAND_SIZE;
	buf->complete = mlx_tls_kfree_complete;

	ret = mlx5_fpga_sbu_conn_sendmsg(mdev->fpga->tls->conn, buf);
	if (ret < 0)
		kfree(buf);

	return ret;
}