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
struct ttm_bo_device {int dummy; } ;
struct vmw_private {struct ttm_bo_device bdev; } ;
struct TYPE_2__ {int priority; } ;
struct vmw_buffer_object {TYPE_1__ base; int /*<<< orphan*/  res_list; } ;
struct ttm_placement {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int TTM_MAX_BO_PRIORITY ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  memset (struct vmw_buffer_object*,int /*<<< orphan*/ ,int) ; 
 int ttm_bo_init (struct ttm_bo_device*,TYPE_1__*,size_t,int /*<<< orphan*/ ,struct ttm_placement*,int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void (*) (struct ttm_buffer_object*)) ; 
 int /*<<< orphan*/  ttm_bo_type_device ; 
 size_t vmw_bo_acc_size (struct vmw_private*,size_t,int) ; 
 void vmw_bo_bo_free (struct ttm_buffer_object*) ; 
 void vmw_user_bo_destroy (struct ttm_buffer_object*) ; 

int vmw_bo_init(struct vmw_private *dev_priv,
		struct vmw_buffer_object *vmw_bo,
		size_t size, struct ttm_placement *placement,
		bool interruptible,
		void (*bo_free)(struct ttm_buffer_object *bo))
{
	struct ttm_bo_device *bdev = &dev_priv->bdev;
	size_t acc_size;
	int ret;
	bool user = (bo_free == &vmw_user_bo_destroy);

	WARN_ON_ONCE(!bo_free && (!user && (bo_free != vmw_bo_bo_free)));

	acc_size = vmw_bo_acc_size(dev_priv, size, user);
	memset(vmw_bo, 0, sizeof(*vmw_bo));
	BUILD_BUG_ON(TTM_MAX_BO_PRIORITY <= 3);
	vmw_bo->base.priority = 3;

	INIT_LIST_HEAD(&vmw_bo->res_list);

	ret = ttm_bo_init(bdev, &vmw_bo->base, size,
			  ttm_bo_type_device, placement,
			  0, interruptible, acc_size,
			  NULL, NULL, bo_free);
	return ret;
}