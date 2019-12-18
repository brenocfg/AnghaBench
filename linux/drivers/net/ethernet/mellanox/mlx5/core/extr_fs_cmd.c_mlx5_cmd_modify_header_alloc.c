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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_modify_hdr {int /*<<< orphan*/  id; } ;
struct mlx5_flow_root_namespace {struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  int /*<<< orphan*/  out ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int FS_FT_ESW_INGRESS_ACL ; 
 int FS_FT_FDB ; 
 int FS_FT_NIC_RX ; 
 int FS_FT_NIC_TX ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX5_CAP_ESW_FLOWTABLE_FDB (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int MLX5_CAP_ESW_INGRESS_ACL (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int MLX5_CAP_FLOWTABLE_NIC_RX (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int MLX5_CAP_FLOWTABLE_NIC_TX (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int MLX5_CMD_OP_ALLOC_MODIFY_HEADER_CONTEXT ; 
#define  MLX5_FLOW_NAMESPACE_BYPASS 132 
#define  MLX5_FLOW_NAMESPACE_EGRESS 131 
#define  MLX5_FLOW_NAMESPACE_ESW_INGRESS 130 
#define  MLX5_FLOW_NAMESPACE_FDB 129 
#define  MLX5_FLOW_NAMESPACE_KERNEL 128 
 int /*<<< orphan*/  MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_DW (int /*<<< orphan*/ ) ; 
 int MLX5_UN_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  actions ; 
 int /*<<< orphan*/  alloc_modify_header_context_in ; 
 int /*<<< orphan*/  alloc_modify_header_context_out ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_modify_header_actions ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mlx5_cmd_exec (struct mlx5_core_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int,int) ; 
 int /*<<< orphan*/  modify_header_id ; 
 int num_of_actions ; 
 int opcode ; 
 int /*<<< orphan*/  set_action_in_add_action_in_auto ; 

__attribute__((used)) static int mlx5_cmd_modify_header_alloc(struct mlx5_flow_root_namespace *ns,
					u8 namespace, u8 num_actions,
					void *modify_actions,
					struct mlx5_modify_hdr *modify_hdr)
{
	u32 out[MLX5_ST_SZ_DW(alloc_modify_header_context_out)];
	int max_actions, actions_size, inlen, err;
	struct mlx5_core_dev *dev = ns->dev;
	void *actions_in;
	u8 table_type;
	u32 *in;

	switch (namespace) {
	case MLX5_FLOW_NAMESPACE_FDB:
		max_actions = MLX5_CAP_ESW_FLOWTABLE_FDB(dev, max_modify_header_actions);
		table_type = FS_FT_FDB;
		break;
	case MLX5_FLOW_NAMESPACE_KERNEL:
	case MLX5_FLOW_NAMESPACE_BYPASS:
		max_actions = MLX5_CAP_FLOWTABLE_NIC_RX(dev, max_modify_header_actions);
		table_type = FS_FT_NIC_RX;
		break;
	case MLX5_FLOW_NAMESPACE_EGRESS:
		max_actions = MLX5_CAP_FLOWTABLE_NIC_TX(dev, max_modify_header_actions);
		table_type = FS_FT_NIC_TX;
		break;
	case MLX5_FLOW_NAMESPACE_ESW_INGRESS:
		max_actions = MLX5_CAP_ESW_INGRESS_ACL(dev, max_modify_header_actions);
		table_type = FS_FT_ESW_INGRESS_ACL;
		break;
	default:
		return -EOPNOTSUPP;
	}

	if (num_actions > max_actions) {
		mlx5_core_warn(dev, "too many modify header actions %d, max supported %d\n",
			       num_actions, max_actions);
		return -EOPNOTSUPP;
	}

	actions_size = MLX5_UN_SZ_BYTES(set_action_in_add_action_in_auto) * num_actions;
	inlen = MLX5_ST_SZ_BYTES(alloc_modify_header_context_in) + actions_size;

	in = kzalloc(inlen, GFP_KERNEL);
	if (!in)
		return -ENOMEM;

	MLX5_SET(alloc_modify_header_context_in, in, opcode,
		 MLX5_CMD_OP_ALLOC_MODIFY_HEADER_CONTEXT);
	MLX5_SET(alloc_modify_header_context_in, in, table_type, table_type);
	MLX5_SET(alloc_modify_header_context_in, in, num_of_actions, num_actions);

	actions_in = MLX5_ADDR_OF(alloc_modify_header_context_in, in, actions);
	memcpy(actions_in, modify_actions, actions_size);

	memset(out, 0, sizeof(out));
	err = mlx5_cmd_exec(dev, in, inlen, out, sizeof(out));

	modify_hdr->id = MLX5_GET(alloc_modify_header_context_out, out, modify_header_id);
	kfree(in);
	return err;
}