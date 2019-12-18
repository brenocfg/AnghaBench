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
typedef  int u16 ;

/* Variables and functions */
#define  MLX5_CMD_OP_QUERY_ESW_VPORT_CONTEXT 130 
#define  MLX5_CMD_OP_QUERY_HCA_CAP 129 
#define  MLX5_CMD_OP_QUERY_HCA_VPORT_CONTEXT 128 
 int MLX5_GET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  general_obj_in_cmd_hdr ; 
 int opcode ; 

__attribute__((used)) static bool devx_is_whitelist_cmd(void *in)
{
	u16 opcode = MLX5_GET(general_obj_in_cmd_hdr, in, opcode);

	switch (opcode) {
	case MLX5_CMD_OP_QUERY_HCA_CAP:
	case MLX5_CMD_OP_QUERY_HCA_VPORT_CONTEXT:
	case MLX5_CMD_OP_QUERY_ESW_VPORT_CONTEXT:
		return true;
	default:
		return false;
	}
}