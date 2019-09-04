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
struct vmw_private {int /*<<< orphan*/  reservation_sem; } ;
struct vmw_buffer_object {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct vmw_buffer_object* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_write_lock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ttm_write_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_bo_bo_free ; 
 int vmw_bo_init (struct vmw_private*,struct vmw_buffer_object*,size_t,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_sys_placement ; 

__attribute__((used)) static int vmw_fb_create_bo(struct vmw_private *vmw_priv,
			    size_t size, struct vmw_buffer_object **out)
{
	struct vmw_buffer_object *vmw_bo;
	int ret;

	(void) ttm_write_lock(&vmw_priv->reservation_sem, false);

	vmw_bo = kmalloc(sizeof(*vmw_bo), GFP_KERNEL);
	if (!vmw_bo) {
		ret = -ENOMEM;
		goto err_unlock;
	}

	ret = vmw_bo_init(vmw_priv, vmw_bo, size,
			      &vmw_sys_placement,
			      false,
			      &vmw_bo_bo_free);
	if (unlikely(ret != 0))
		goto err_unlock; /* init frees the buffer on failure */

	*out = vmw_bo;
	ttm_write_unlock(&vmw_priv->reservation_sem);

	return 0;

err_unlock:
	ttm_write_unlock(&vmw_priv->reservation_sem);
	return ret;
}