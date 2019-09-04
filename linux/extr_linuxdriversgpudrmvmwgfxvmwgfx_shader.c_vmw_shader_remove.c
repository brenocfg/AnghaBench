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
struct vmw_resource {int dummy; } ;
struct vmw_cmdbuf_res_manager {int dummy; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  SVGA3dShaderType ;

/* Variables and functions */
 int EINVAL ; 
 int vmw_cmdbuf_res_remove (struct vmw_cmdbuf_res_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct list_head*,struct vmw_resource**) ; 
 int /*<<< orphan*/  vmw_cmdbuf_res_shader ; 
 int /*<<< orphan*/  vmw_shader_id_ok (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_shader_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vmw_shader_remove(struct vmw_cmdbuf_res_manager *man,
		      u32 user_key, SVGA3dShaderType shader_type,
		      struct list_head *list)
{
	struct vmw_resource *dummy;

	if (!vmw_shader_id_ok(user_key, shader_type))
		return -EINVAL;

	return vmw_cmdbuf_res_remove(man, vmw_cmdbuf_res_shader,
				     vmw_shader_key(user_key, shader_type),
				     list, &dummy);
}