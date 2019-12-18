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
struct vmw_resource {scalar_t__ backup_size; int /*<<< orphan*/ * backup; TYPE_1__* func; int /*<<< orphan*/  lru_head; struct vmw_private* dev_priv; } ;
struct vmw_private {int /*<<< orphan*/  resource_lock; } ;
struct TYPE_2__ {scalar_t__ needs_backup; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned long) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int vmw_resource_buf_alloc (struct vmw_resource*,int) ; 

int vmw_resource_reserve(struct vmw_resource *res, bool interruptible,
			 bool no_backup)
{
	struct vmw_private *dev_priv = res->dev_priv;
	int ret;

	spin_lock(&dev_priv->resource_lock);
	list_del_init(&res->lru_head);
	spin_unlock(&dev_priv->resource_lock);

	if (res->func->needs_backup && res->backup == NULL &&
	    !no_backup) {
		ret = vmw_resource_buf_alloc(res, interruptible);
		if (unlikely(ret != 0)) {
			DRM_ERROR("Failed to allocate a backup buffer "
				  "of size %lu. bytes\n",
				  (unsigned long) res->backup_size);
			return ret;
		}
	}

	return 0;
}