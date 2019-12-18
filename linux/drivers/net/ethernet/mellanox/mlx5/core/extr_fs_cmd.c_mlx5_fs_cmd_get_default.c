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
#define  FS_FT_ESW_EGRESS_ACL 135 
#define  FS_FT_ESW_INGRESS_ACL 134 
#define  FS_FT_FDB 133 
#define  FS_FT_NIC_RX 132 
#define  FS_FT_NIC_TX 131 
#define  FS_FT_RDMA_RX 130 
#define  FS_FT_SNIFFER_RX 129 
#define  FS_FT_SNIFFER_TX 128 
 struct mlx5_flow_cmds const* mlx5_fs_cmd_get_fw_cmds () ; 
 struct mlx5_flow_cmds const* mlx5_fs_cmd_get_stub_cmds () ; 

const struct mlx5_flow_cmds *mlx5_fs_cmd_get_default(enum fs_flow_table_type type)
{
	switch (type) {
	case FS_FT_NIC_RX:
	case FS_FT_ESW_EGRESS_ACL:
	case FS_FT_ESW_INGRESS_ACL:
	case FS_FT_FDB:
	case FS_FT_SNIFFER_RX:
	case FS_FT_SNIFFER_TX:
	case FS_FT_NIC_TX:
	case FS_FT_RDMA_RX:
		return mlx5_fs_cmd_get_fw_cmds();
	default:
		return mlx5_fs_cmd_get_stub_cmds();
	}
}