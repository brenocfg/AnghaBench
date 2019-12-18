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
typedef  int u16 ;
struct mlx5_core_dev {int dummy; } ;
typedef  int /*<<< orphan*/  out ;
struct TYPE_2__ {int /*<<< orphan*/  addresses_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int MLX5_CMD_OP_MODIFY_NIC_VPORT_CONTEXT ; 
 int MLX5_NVPRT_LIST_TYPE_VLAN ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_DW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allowed_list_size ; 
 int /*<<< orphan*/  allowed_list_type ; 
 int /*<<< orphan*/ * current_uc_mac_address ; 
 TYPE_1__ field_select ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_max_vlan_list ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mlx5_cmd_exec (struct mlx5_core_dev*,void*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  modify_nic_vport_context_in ; 
 int /*<<< orphan*/  modify_nic_vport_context_out ; 
 int /*<<< orphan*/  nic_vport_context ; 
 int /*<<< orphan*/  opcode ; 
 int /*<<< orphan*/  vlan ; 
 int /*<<< orphan*/  vlan_layout ; 

int mlx5_modify_nic_vport_vlans(struct mlx5_core_dev *dev,
				u16 vlans[],
				int list_size)
{
	u32 out[MLX5_ST_SZ_DW(modify_nic_vport_context_out)];
	void *nic_vport_ctx;
	int max_list_size;
	int in_sz;
	void *in;
	int err;
	int i;

	max_list_size = 1 << MLX5_CAP_GEN(dev, log_max_vlan_list);

	if (list_size > max_list_size)
		return -ENOSPC;

	in_sz = MLX5_ST_SZ_BYTES(modify_nic_vport_context_in) +
		list_size * MLX5_ST_SZ_BYTES(vlan_layout);

	memset(out, 0, sizeof(out));
	in = kzalloc(in_sz, GFP_KERNEL);
	if (!in)
		return -ENOMEM;

	MLX5_SET(modify_nic_vport_context_in, in, opcode,
		 MLX5_CMD_OP_MODIFY_NIC_VPORT_CONTEXT);
	MLX5_SET(modify_nic_vport_context_in, in,
		 field_select.addresses_list, 1);

	nic_vport_ctx = MLX5_ADDR_OF(modify_nic_vport_context_in, in,
				     nic_vport_context);

	MLX5_SET(nic_vport_context, nic_vport_ctx,
		 allowed_list_type, MLX5_NVPRT_LIST_TYPE_VLAN);
	MLX5_SET(nic_vport_context, nic_vport_ctx,
		 allowed_list_size, list_size);

	for (i = 0; i < list_size; i++) {
		void *vlan_addr = MLX5_ADDR_OF(nic_vport_context,
					       nic_vport_ctx,
					       current_uc_mac_address[i]);
		MLX5_SET(vlan_layout, vlan_addr, vlan, vlans[i]);
	}

	err = mlx5_cmd_exec(dev, in, in_sz, out, sizeof(out));
	kfree(in);
	return err;
}