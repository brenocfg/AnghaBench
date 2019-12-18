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
struct mlx5_flow_cmds {int dummy; } ;
typedef  enum fs_flow_table_type { ____Placeholder_fs_flow_table_type } fs_flow_table_type ;

/* Variables and functions */
#define  FS_FT_NIC_RX 129 
#define  FS_FT_NIC_TX 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct mlx5_flow_cmds const fpga_ipsec_egress ; 
 struct mlx5_flow_cmds const fpga_ipsec_ingress ; 

const struct mlx5_flow_cmds *mlx5_fs_cmd_get_default_ipsec_fpga_cmds(enum fs_flow_table_type type)
{
	switch (type) {
	case FS_FT_NIC_RX:
		return &fpga_ipsec_ingress;
	case FS_FT_NIC_TX:
		return &fpga_ipsec_egress;
	default:
		WARN_ON(true);
		return NULL;
	}
}