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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_core {TYPE_2__* bus_info; int /*<<< orphan*/  bus_priv; TYPE_1__* bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int (* cmd_exec ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,char*,size_t,char*,size_t,scalar_t__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 int ETIMEDOUT ; 
 scalar_t__ MLXSW_CMD_STATUS_OK ; 
 scalar_t__ MLXSW_CMD_STATUS_RUNNING_RESET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mlxsw_cmd_opcode_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_cmd_status_str (scalar_t__) ; 
 int /*<<< orphan*/  mlxsw_core_buf_dump_dbg (struct mlxsw_core*,char*,size_t) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,char*,size_t,char*,size_t,scalar_t__*) ; 

int mlxsw_cmd_exec(struct mlxsw_core *mlxsw_core, u16 opcode, u8 opcode_mod,
		   u32 in_mod, bool out_mbox_direct, bool reset_ok,
		   char *in_mbox, size_t in_mbox_size,
		   char *out_mbox, size_t out_mbox_size)
{
	u8 status;
	int err;

	BUG_ON(in_mbox_size % sizeof(u32) || out_mbox_size % sizeof(u32));
	if (!mlxsw_core->bus->cmd_exec)
		return -EOPNOTSUPP;

	dev_dbg(mlxsw_core->bus_info->dev, "Cmd exec (opcode=%x(%s),opcode_mod=%x,in_mod=%x)\n",
		opcode, mlxsw_cmd_opcode_str(opcode), opcode_mod, in_mod);
	if (in_mbox) {
		dev_dbg(mlxsw_core->bus_info->dev, "Input mailbox:\n");
		mlxsw_core_buf_dump_dbg(mlxsw_core, in_mbox, in_mbox_size);
	}

	err = mlxsw_core->bus->cmd_exec(mlxsw_core->bus_priv, opcode,
					opcode_mod, in_mod, out_mbox_direct,
					in_mbox, in_mbox_size,
					out_mbox, out_mbox_size, &status);

	if (!err && out_mbox) {
		dev_dbg(mlxsw_core->bus_info->dev, "Output mailbox:\n");
		mlxsw_core_buf_dump_dbg(mlxsw_core, out_mbox, out_mbox_size);
	}

	if (reset_ok && err == -EIO &&
	    status == MLXSW_CMD_STATUS_RUNNING_RESET) {
		err = 0;
	} else if (err == -EIO && status != MLXSW_CMD_STATUS_OK) {
		dev_err(mlxsw_core->bus_info->dev, "Cmd exec failed (opcode=%x(%s),opcode_mod=%x,in_mod=%x,status=%x(%s))\n",
			opcode, mlxsw_cmd_opcode_str(opcode), opcode_mod,
			in_mod, status, mlxsw_cmd_status_str(status));
	} else if (err == -ETIMEDOUT) {
		dev_err(mlxsw_core->bus_info->dev, "Cmd exec timed-out (opcode=%x(%s),opcode_mod=%x,in_mod=%x)\n",
			opcode, mlxsw_cmd_opcode_str(opcode), opcode_mod,
			in_mod);
	}

	return err;
}