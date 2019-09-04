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
struct vmw_resource {struct vmw_private* dev_priv; } ;
struct vmw_private {int dummy; } ;
struct vmw_dx_shader {int /*<<< orphan*/  cotable; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vmw_dx_shader*) ; 
 int /*<<< orphan*/  ttm_mem_global_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_mem_glob (struct vmw_private*) ; 
 struct vmw_dx_shader* vmw_res_to_dx_shader (struct vmw_resource*) ; 
 int /*<<< orphan*/  vmw_resource_unreference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_shader_dx_size ; 

__attribute__((used)) static void vmw_dx_shader_res_free(struct vmw_resource *res)
{
	struct vmw_private *dev_priv = res->dev_priv;
	struct vmw_dx_shader *shader = vmw_res_to_dx_shader(res);

	vmw_resource_unreference(&shader->cotable);
	kfree(shader);
	ttm_mem_global_free(vmw_mem_glob(dev_priv), vmw_shader_dx_size);
}