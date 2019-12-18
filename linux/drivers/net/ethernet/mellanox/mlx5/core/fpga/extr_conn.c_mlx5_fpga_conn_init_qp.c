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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_9__ {int /*<<< orphan*/  pdn; } ;
struct mlx5_fpga_device {TYPE_1__ conn_res; struct mlx5_core_dev* mdev; } ;
struct TYPE_16__ {int /*<<< orphan*/  qpn; } ;
struct TYPE_12__ {int /*<<< orphan*/  dma; } ;
struct TYPE_13__ {TYPE_4__ db; } ;
struct TYPE_14__ {TYPE_8__ mqp; TYPE_5__ wq_ctrl; } ;
struct TYPE_10__ {int /*<<< orphan*/  cqn; } ;
struct TYPE_11__ {TYPE_2__ mcq; } ;
struct mlx5_fpga_conn {TYPE_6__ qp; TYPE_3__ cq; struct mlx5_fpga_device* fdev; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_15__ {int /*<<< orphan*/  vhca_port_num; int /*<<< orphan*/  pkey_index; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLX5_CMD_OP_RST2INIT_QP ; 
 int /*<<< orphan*/  MLX5_FPGA_PKEY_INDEX ; 
 int /*<<< orphan*/  MLX5_FPGA_PORT_NUM ; 
 int /*<<< orphan*/  MLX5_QP_PM_MIGRATED ; 
 int /*<<< orphan*/  MLX5_QP_ST_RC ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_ST_SZ_BYTES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cqn_rcv ; 
 int /*<<< orphan*/  cqn_snd ; 
 int /*<<< orphan*/  dbr_addr ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5_core_qp_modify (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_8__*) ; 
 int /*<<< orphan*/  mlx5_fpga_dbg (struct mlx5_fpga_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fpga_warn (struct mlx5_fpga_device*,char*,int) ; 
 int /*<<< orphan*/  pd ; 
 int /*<<< orphan*/  pm_state ; 
 TYPE_7__ primary_address_path ; 
 int /*<<< orphan*/  st ; 

__attribute__((used)) static inline int mlx5_fpga_conn_init_qp(struct mlx5_fpga_conn *conn)
{
	struct mlx5_fpga_device *fdev = conn->fdev;
	struct mlx5_core_dev *mdev = fdev->mdev;
	u32 *qpc = NULL;
	int err;

	mlx5_fpga_dbg(conn->fdev, "Modifying QP %u to INIT\n", conn->qp.mqp.qpn);

	qpc = kzalloc(MLX5_ST_SZ_BYTES(qpc), GFP_KERNEL);
	if (!qpc) {
		err = -ENOMEM;
		goto out;
	}

	MLX5_SET(qpc, qpc, st, MLX5_QP_ST_RC);
	MLX5_SET(qpc, qpc, pm_state, MLX5_QP_PM_MIGRATED);
	MLX5_SET(qpc, qpc, primary_address_path.pkey_index, MLX5_FPGA_PKEY_INDEX);
	MLX5_SET(qpc, qpc, primary_address_path.vhca_port_num, MLX5_FPGA_PORT_NUM);
	MLX5_SET(qpc, qpc, pd, conn->fdev->conn_res.pdn);
	MLX5_SET(qpc, qpc, cqn_snd, conn->cq.mcq.cqn);
	MLX5_SET(qpc, qpc, cqn_rcv, conn->cq.mcq.cqn);
	MLX5_SET64(qpc, qpc, dbr_addr, conn->qp.wq_ctrl.db.dma);

	err = mlx5_core_qp_modify(mdev, MLX5_CMD_OP_RST2INIT_QP, 0, qpc,
				  &conn->qp.mqp);
	if (err) {
		mlx5_fpga_warn(fdev, "qp_modify RST2INIT failed: %d\n", err);
		goto out;
	}

out:
	kfree(qpc);
	return err;
}