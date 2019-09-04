#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct mlx5_fpga_conn {int /*<<< orphan*/  fdev; } ;
struct mlx5_err_cqe {int syndrome; } ;
struct mlx5_cqe64 {int op_own; } ;

/* Variables and functions */
#define  MLX5_CQE_REQ 131 
#define  MLX5_CQE_REQ_ERR 130 
#define  MLX5_CQE_RESP_ERR 129 
#define  MLX5_CQE_RESP_SEND 128 
 int /*<<< orphan*/  mlx5_fpga_conn_rq_cqe (struct mlx5_fpga_conn*,struct mlx5_cqe64*,int) ; 
 int /*<<< orphan*/  mlx5_fpga_conn_sq_cqe (struct mlx5_fpga_conn*,struct mlx5_cqe64*,int) ; 
 int /*<<< orphan*/  mlx5_fpga_warn (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void mlx5_fpga_conn_handle_cqe(struct mlx5_fpga_conn *conn,
				      struct mlx5_cqe64 *cqe)
{
	u8 opcode, status = 0;

	opcode = cqe->op_own >> 4;

	switch (opcode) {
	case MLX5_CQE_REQ_ERR:
		status = ((struct mlx5_err_cqe *)cqe)->syndrome;
		/* Fall through */
	case MLX5_CQE_REQ:
		mlx5_fpga_conn_sq_cqe(conn, cqe, status);
		break;

	case MLX5_CQE_RESP_ERR:
		status = ((struct mlx5_err_cqe *)cqe)->syndrome;
		/* Fall through */
	case MLX5_CQE_RESP_SEND:
		mlx5_fpga_conn_rq_cqe(conn, cqe, status);
		break;
	default:
		mlx5_fpga_warn(conn->fdev, "Unexpected cqe opcode %u\n",
			       opcode);
	}
}