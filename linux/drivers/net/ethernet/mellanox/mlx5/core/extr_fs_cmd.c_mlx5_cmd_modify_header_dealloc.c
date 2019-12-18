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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_modify_hdr {int /*<<< orphan*/  id; } ;
struct mlx5_flow_root_namespace {struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  int /*<<< orphan*/  out ;
typedef  int /*<<< orphan*/  in ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_CMD_OP_DEALLOC_MODIFY_HEADER_CONTEXT ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_DW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dealloc_modify_header_context_in ; 
 int /*<<< orphan*/  dealloc_modify_header_context_out ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_cmd_exec (struct mlx5_core_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  modify_header_id ; 
 int /*<<< orphan*/  opcode ; 

__attribute__((used)) static void mlx5_cmd_modify_header_dealloc(struct mlx5_flow_root_namespace *ns,
					   struct mlx5_modify_hdr *modify_hdr)
{
	u32 in[MLX5_ST_SZ_DW(dealloc_modify_header_context_in)];
	u32 out[MLX5_ST_SZ_DW(dealloc_modify_header_context_out)];
	struct mlx5_core_dev *dev = ns->dev;

	memset(in, 0, sizeof(in));
	MLX5_SET(dealloc_modify_header_context_in, in, opcode,
		 MLX5_CMD_OP_DEALLOC_MODIFY_HEADER_CONTEXT);
	MLX5_SET(dealloc_modify_header_context_in, in, modify_header_id,
		 modify_hdr->id);

	mlx5_cmd_exec(dev, in, sizeof(in), out, sizeof(out));
}