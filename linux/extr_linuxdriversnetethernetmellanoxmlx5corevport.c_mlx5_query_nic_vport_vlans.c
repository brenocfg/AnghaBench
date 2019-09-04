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
typedef  int u32 ;
typedef  void* u16 ;
struct mlx5_core_dev {int dummy; } ;
typedef  int /*<<< orphan*/  in ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int MLX5_CMD_OP_QUERY_NIC_VPORT_CONTEXT ; 
 void* MLX5_GET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int MLX5_NVPRT_LIST_TYPE_VLAN ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_DW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allowed_list_size ; 
 int /*<<< orphan*/  allowed_list_type ; 
 int /*<<< orphan*/ * current_uc_mac_address ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_max_vlan_list ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int mlx5_cmd_exec (struct mlx5_core_dev*,int*,int,void*,int) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int,int) ; 
 int /*<<< orphan*/  modify_nic_vport_context_in ; 
 int /*<<< orphan*/  nic_vport_context ; 
 int /*<<< orphan*/  opcode ; 
 int /*<<< orphan*/  other_vport ; 
 int /*<<< orphan*/  query_nic_vport_context_in ; 
 int /*<<< orphan*/  query_nic_vport_context_out ; 
 int /*<<< orphan*/  vlan ; 
 int /*<<< orphan*/  vlan_layout ; 
 int /*<<< orphan*/  vport_number ; 

int mlx5_query_nic_vport_vlans(struct mlx5_core_dev *dev,
			       u32 vport,
			       u16 vlans[],
			       int *size)
{
	u32 in[MLX5_ST_SZ_DW(query_nic_vport_context_in)];
	void *nic_vport_ctx;
	int req_list_size;
	int max_list_size;
	int out_sz;
	void *out;
	int err;
	int i;

	req_list_size = *size;
	max_list_size = 1 << MLX5_CAP_GEN(dev, log_max_vlan_list);
	if (req_list_size > max_list_size) {
		mlx5_core_warn(dev, "Requested list size (%d) > (%d) max list size\n",
			       req_list_size, max_list_size);
		req_list_size = max_list_size;
	}

	out_sz = MLX5_ST_SZ_BYTES(modify_nic_vport_context_in) +
			req_list_size * MLX5_ST_SZ_BYTES(vlan_layout);

	memset(in, 0, sizeof(in));
	out = kzalloc(out_sz, GFP_KERNEL);
	if (!out)
		return -ENOMEM;

	MLX5_SET(query_nic_vport_context_in, in, opcode,
		 MLX5_CMD_OP_QUERY_NIC_VPORT_CONTEXT);
	MLX5_SET(query_nic_vport_context_in, in, allowed_list_type,
		 MLX5_NVPRT_LIST_TYPE_VLAN);
	MLX5_SET(query_nic_vport_context_in, in, vport_number, vport);

	if (vport)
		MLX5_SET(query_nic_vport_context_in, in, other_vport, 1);

	err = mlx5_cmd_exec(dev, in, sizeof(in), out, out_sz);
	if (err)
		goto out;

	nic_vport_ctx = MLX5_ADDR_OF(query_nic_vport_context_out, out,
				     nic_vport_context);
	req_list_size = MLX5_GET(nic_vport_context, nic_vport_ctx,
				 allowed_list_size);

	*size = req_list_size;
	for (i = 0; i < req_list_size; i++) {
		void *vlan_addr = MLX5_ADDR_OF(nic_vport_context,
					       nic_vport_ctx,
					       current_uc_mac_address[i]);
		vlans[i] = MLX5_GET(vlan_layout, vlan_addr, vlan);
	}
out:
	kfree(out);
	return err;
}