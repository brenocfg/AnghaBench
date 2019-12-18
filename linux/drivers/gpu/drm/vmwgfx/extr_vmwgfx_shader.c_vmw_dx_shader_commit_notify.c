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
struct vmw_resource {int id; struct vmw_private* dev_priv; } ;
struct vmw_private {int /*<<< orphan*/  binding_mutex; } ;
struct vmw_dx_shader {int committed; int id; int /*<<< orphan*/  cotable_head; int /*<<< orphan*/  cotable; } ;
typedef  enum vmw_cmdbuf_res_state { ____Placeholder_vmw_cmdbuf_res_state } vmw_cmdbuf_res_state ;

/* Variables and functions */
 int VMW_CMDBUF_RES_ADD ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_cotable_add_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct vmw_dx_shader* vmw_res_to_dx_shader (struct vmw_resource*) ; 

__attribute__((used)) static void vmw_dx_shader_commit_notify(struct vmw_resource *res,
					enum vmw_cmdbuf_res_state state)
{
	struct vmw_dx_shader *shader = vmw_res_to_dx_shader(res);
	struct vmw_private *dev_priv = res->dev_priv;

	if (state == VMW_CMDBUF_RES_ADD) {
		mutex_lock(&dev_priv->binding_mutex);
		vmw_cotable_add_resource(shader->cotable,
					 &shader->cotable_head);
		shader->committed = true;
		res->id = shader->id;
		mutex_unlock(&dev_priv->binding_mutex);
	} else {
		mutex_lock(&dev_priv->binding_mutex);
		list_del_init(&shader->cotable_head);
		shader->committed = false;
		res->id = -1;
		mutex_unlock(&dev_priv->binding_mutex);
	}
}