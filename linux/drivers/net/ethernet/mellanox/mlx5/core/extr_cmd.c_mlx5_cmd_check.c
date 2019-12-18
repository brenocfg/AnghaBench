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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX5_CMD_OP_DESTROY_MKEY ; 
 scalar_t__ MLX5_GET (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  cmd_status_str (int /*<<< orphan*/ ) ; 
 int cmd_status_to_err (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_in ; 
 int /*<<< orphan*/  mlx5_cmd_mbox_status (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_command_str (scalar_t__) ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_err_rl (struct mlx5_core_dev*,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5_cmd_check(struct mlx5_core_dev *dev, void *in, void *out)
{
	u32 syndrome;
	u8  status;
	u16 opcode;
	u16 op_mod;
	u16 uid;

	mlx5_cmd_mbox_status(out, &status, &syndrome);
	if (!status)
		return 0;

	opcode = MLX5_GET(mbox_in, in, opcode);
	op_mod = MLX5_GET(mbox_in, in, op_mod);
	uid    = MLX5_GET(mbox_in, in, uid);

	if (!uid && opcode != MLX5_CMD_OP_DESTROY_MKEY)
		mlx5_core_err_rl(dev,
			"%s(0x%x) op_mod(0x%x) failed, status %s(0x%x), syndrome (0x%x)\n",
			mlx5_command_str(opcode), opcode, op_mod,
			cmd_status_str(status), status, syndrome);
	else
		mlx5_core_dbg(dev,
		      "%s(0x%x) op_mod(0x%x) failed, status %s(0x%x), syndrome (0x%x)\n",
		      mlx5_command_str(opcode),
		      opcode, op_mod,
		      cmd_status_str(status),
		      status,
		      syndrome);

	return cmd_status_to_err(status);
}