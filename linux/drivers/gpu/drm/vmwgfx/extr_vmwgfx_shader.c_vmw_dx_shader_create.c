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
struct vmw_resource {int /*<<< orphan*/  id; struct vmw_private* dev_priv; } ;
struct vmw_private {int /*<<< orphan*/  binding_mutex; } ;
struct vmw_dx_shader {int /*<<< orphan*/  id; int /*<<< orphan*/  committed; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vmw_dx_shader_unscrub (struct vmw_resource*) ; 
 struct vmw_dx_shader* vmw_res_to_dx_shader (struct vmw_resource*) ; 
 scalar_t__ vmw_resource_mob_attached (struct vmw_resource*) ; 

__attribute__((used)) static int vmw_dx_shader_create(struct vmw_resource *res)
{
	struct vmw_private *dev_priv = res->dev_priv;
	struct vmw_dx_shader *shader = vmw_res_to_dx_shader(res);
	int ret = 0;

	WARN_ON_ONCE(!shader->committed);

	if (vmw_resource_mob_attached(res)) {
		mutex_lock(&dev_priv->binding_mutex);
		ret = vmw_dx_shader_unscrub(res);
		mutex_unlock(&dev_priv->binding_mutex);
	}

	res->id = shader->id;
	return ret;
}