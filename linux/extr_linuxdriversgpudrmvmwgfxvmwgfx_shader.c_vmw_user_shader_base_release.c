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
struct vmw_resource {int dummy; } ;
struct ttm_base_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmw_resource_unreference (struct vmw_resource**) ; 
 struct vmw_resource* vmw_user_shader_base_to_res (struct ttm_base_object*) ; 

__attribute__((used)) static void vmw_user_shader_base_release(struct ttm_base_object **p_base)
{
	struct ttm_base_object *base = *p_base;
	struct vmw_resource *res = vmw_user_shader_base_to_res(base);

	*p_base = NULL;
	vmw_resource_unreference(&res);
}