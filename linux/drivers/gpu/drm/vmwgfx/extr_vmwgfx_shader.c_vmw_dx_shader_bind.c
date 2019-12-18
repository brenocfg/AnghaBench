#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vmw_resource {struct vmw_private* dev_priv; } ;
struct vmw_private {int /*<<< orphan*/  binding_mutex; } ;
struct ttm_validate_buffer {struct ttm_buffer_object* bo; } ;
struct TYPE_2__ {scalar_t__ mem_type; } ;
struct ttm_buffer_object {TYPE_1__ mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ VMW_PL_MOB ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_dx_shader_unscrub (struct vmw_resource*) ; 

__attribute__((used)) static int vmw_dx_shader_bind(struct vmw_resource *res,
			      struct ttm_validate_buffer *val_buf)
{
	struct vmw_private *dev_priv = res->dev_priv;
	struct ttm_buffer_object *bo = val_buf->bo;

	BUG_ON(bo->mem.mem_type != VMW_PL_MOB);
	mutex_lock(&dev_priv->binding_mutex);
	vmw_dx_shader_unscrub(res);
	mutex_unlock(&dev_priv->binding_mutex);

	return 0;
}