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
struct mlxsw_reg_info {scalar_t__ id; int /*<<< orphan*/  len; } ;
struct mlxsw_core {TYPE_1__* bus_info; } ;
typedef  enum mlxsw_emad_op_tlv_status { ____Placeholder_mlxsw_emad_op_tlv_status } mlxsw_emad_op_tlv_status ;
typedef  enum mlxsw_core_reg_access_type { ____Placeholder_mlxsw_core_reg_access_type } mlxsw_core_reg_access_type ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MLXSW_EMAD_MAX_RETRY ; 
 int MLXSW_EMAD_OP_TLV_LEN ; 
 scalar_t__ MLXSW_REG_MRSR_ID ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_cmd_access_reg (struct mlxsw_core*,int,char*,char*) ; 
 char* mlxsw_cmd_mbox_alloc () ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_free (char*) ; 
 int /*<<< orphan*/  mlxsw_core_reg_access_type_str (int) ; 
 int /*<<< orphan*/  mlxsw_core_tid_get (struct mlxsw_core*) ; 
 int /*<<< orphan*/  mlxsw_emad_op_tlv_status_str (int) ; 
 int /*<<< orphan*/  mlxsw_emad_pack_op_tlv (char*,struct mlxsw_reg_info const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_emad_pack_reg_tlv (char*,struct mlxsw_reg_info const*,char*) ; 
 int mlxsw_emad_process_status (char*,int*) ; 
 int /*<<< orphan*/  mlxsw_emad_reg_payload (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_id_str (scalar_t__) ; 

__attribute__((used)) static int mlxsw_core_reg_access_cmd(struct mlxsw_core *mlxsw_core,
				     const struct mlxsw_reg_info *reg,
				     char *payload,
				     enum mlxsw_core_reg_access_type type)
{
	enum mlxsw_emad_op_tlv_status status;
	int err, n_retry;
	bool reset_ok;
	char *in_mbox, *out_mbox, *tmp;

	dev_dbg(mlxsw_core->bus_info->dev, "Reg cmd access (reg_id=%x(%s),type=%s)\n",
		reg->id, mlxsw_reg_id_str(reg->id),
		mlxsw_core_reg_access_type_str(type));

	in_mbox = mlxsw_cmd_mbox_alloc();
	if (!in_mbox)
		return -ENOMEM;

	out_mbox = mlxsw_cmd_mbox_alloc();
	if (!out_mbox) {
		err = -ENOMEM;
		goto free_in_mbox;
	}

	mlxsw_emad_pack_op_tlv(in_mbox, reg, type,
			       mlxsw_core_tid_get(mlxsw_core));
	tmp = in_mbox + MLXSW_EMAD_OP_TLV_LEN * sizeof(u32);
	mlxsw_emad_pack_reg_tlv(tmp, reg, payload);

	/* There is a special treatment needed for MRSR (reset) register.
	 * The command interface will return error after the command
	 * is executed, so tell the lower layer to expect it
	 * and cope accordingly.
	 */
	reset_ok = reg->id == MLXSW_REG_MRSR_ID;

	n_retry = 0;
retry:
	err = mlxsw_cmd_access_reg(mlxsw_core, reset_ok, in_mbox, out_mbox);
	if (!err) {
		err = mlxsw_emad_process_status(out_mbox, &status);
		if (err) {
			if (err == -EAGAIN && n_retry++ < MLXSW_EMAD_MAX_RETRY)
				goto retry;
			dev_err(mlxsw_core->bus_info->dev, "Reg cmd access status failed (status=%x(%s))\n",
				status, mlxsw_emad_op_tlv_status_str(status));
		}
	}

	if (!err)
		memcpy(payload, mlxsw_emad_reg_payload(out_mbox),
		       reg->len);

	mlxsw_cmd_mbox_free(out_mbox);
free_in_mbox:
	mlxsw_cmd_mbox_free(in_mbox);
	if (err)
		dev_err(mlxsw_core->bus_info->dev, "Reg cmd access failed (reg_id=%x(%s),type=%s)\n",
			reg->id, mlxsw_reg_id_str(reg->id),
			mlxsw_core_reg_access_type_str(type));
	return err;
}