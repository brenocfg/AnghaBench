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
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int MLX5_CMD_OP_QUERY_VPORT_COUNTER ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int,int) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_cmd_exec (struct mlx5_core_dev*,void*,int,void*,size_t) ; 
 int /*<<< orphan*/  num_ports ; 
 int opcode ; 
 int /*<<< orphan*/  query_vport_counter_in ; 
 int /*<<< orphan*/  vport_group_manager ; 
 int vport_number ; 

int mlx5_core_query_vport_counter(struct mlx5_core_dev *dev, u8 other_vport,
				  int vf, u8 port_num, void *out,
				  size_t out_sz)
{
	int	in_sz = MLX5_ST_SZ_BYTES(query_vport_counter_in);
	int	is_group_manager;
	void   *in;
	int	err;

	is_group_manager = MLX5_CAP_GEN(dev, vport_group_manager);
	in = kvzalloc(in_sz, GFP_KERNEL);
	if (!in) {
		err = -ENOMEM;
		return err;
	}

	MLX5_SET(query_vport_counter_in, in, opcode,
		 MLX5_CMD_OP_QUERY_VPORT_COUNTER);
	if (other_vport) {
		if (is_group_manager) {
			MLX5_SET(query_vport_counter_in, in, other_vport, 1);
			MLX5_SET(query_vport_counter_in, in, vport_number, vf + 1);
		} else {
			err = -EPERM;
			goto free;
		}
	}
	if (MLX5_CAP_GEN(dev, num_ports) == 2)
		MLX5_SET(query_vport_counter_in, in, port_num, port_num);

	err = mlx5_cmd_exec(dev, in, in_sz, out,  out_sz);
free:
	kvfree(in);
	return err;
}