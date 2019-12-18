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
typedef  void* u32 ;
typedef  scalar_t__ u16 ;
struct devx_obj {int /*<<< orphan*/  dinbox; } ;

/* Variables and functions */
 scalar_t__ MLX5_CMD_OP_DEALLOC_FLOW_COUNTER ; 
 void* MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dealloc_flow_counter_in ; 
 int /*<<< orphan*/  flow_counter_id ; 
 int /*<<< orphan*/  general_obj_in_cmd_hdr ; 
 scalar_t__ opcode ; 

bool mlx5_ib_devx_is_flow_counter(void *obj, u32 *counter_id)
{
	struct devx_obj *devx_obj = obj;
	u16 opcode = MLX5_GET(general_obj_in_cmd_hdr, devx_obj->dinbox, opcode);

	if (opcode == MLX5_CMD_OP_DEALLOC_FLOW_COUNTER) {
		*counter_id = MLX5_GET(dealloc_flow_counter_in,
				       devx_obj->dinbox,
				       flow_counter_id);
		return true;
	}

	return false;
}