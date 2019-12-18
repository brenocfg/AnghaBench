#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct mlx5_wqe_data_seg {int /*<<< orphan*/  addr; void* lkey; void* byte_count; } ;
struct mlx5_wqe_ctrl_seg {void* qpn_ds; void* opmod_idx_opcode; int /*<<< orphan*/  fm_ce_se; scalar_t__ imm; } ;
struct mlx5_fpga_dma_buf {TYPE_8__* sg; } ;
struct TYPE_14__ {int pc; int size; struct mlx5_fpga_dma_buf** bufs; } ;
struct TYPE_13__ {int qpn; } ;
struct TYPE_9__ {int /*<<< orphan*/  sq; } ;
struct TYPE_15__ {TYPE_6__ sq; TYPE_5__ mqp; TYPE_1__ wq; } ;
struct mlx5_fpga_conn {TYPE_7__ qp; TYPE_4__* fdev; } ;
struct TYPE_16__ {int size; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {int key; } ;
struct TYPE_11__ {TYPE_2__ mkey; } ;
struct TYPE_12__ {TYPE_3__ conn_res; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_8__*) ; 
 int MLX5_OPCODE_SEND ; 
 int /*<<< orphan*/  MLX5_WQE_CTRL_CQ_UPDATE ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fpga_conn_notify_hw (struct mlx5_fpga_conn*,struct mlx5_wqe_ctrl_seg*) ; 
 struct mlx5_wqe_ctrl_seg* mlx5_wq_cyc_get_wqe (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void mlx5_fpga_conn_post_send(struct mlx5_fpga_conn *conn,
				     struct mlx5_fpga_dma_buf *buf)
{
	struct mlx5_wqe_ctrl_seg *ctrl;
	struct mlx5_wqe_data_seg *data;
	unsigned int ix, sgi;
	int size = 1;

	ix = conn->qp.sq.pc & (conn->qp.sq.size - 1);

	ctrl = mlx5_wq_cyc_get_wqe(&conn->qp.wq.sq, ix);
	data = (void *)(ctrl + 1);

	for (sgi = 0; sgi < ARRAY_SIZE(buf->sg); sgi++) {
		if (!buf->sg[sgi].data)
			break;
		data->byte_count = cpu_to_be32(buf->sg[sgi].size);
		data->lkey = cpu_to_be32(conn->fdev->conn_res.mkey.key);
		data->addr = cpu_to_be64(buf->sg[sgi].dma_addr);
		data++;
		size++;
	}

	ctrl->imm = 0;
	ctrl->fm_ce_se = MLX5_WQE_CTRL_CQ_UPDATE;
	ctrl->opmod_idx_opcode = cpu_to_be32(((conn->qp.sq.pc & 0xffff) << 8) |
					     MLX5_OPCODE_SEND);
	ctrl->qpn_ds = cpu_to_be32(size | (conn->qp.mqp.qpn << 8));

	conn->qp.sq.pc++;
	conn->qp.sq.bufs[ix] = buf;
	mlx5_fpga_conn_notify_hw(conn, ctrl);
}