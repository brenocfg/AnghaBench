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
struct TYPE_2__ {int /*<<< orphan*/  userptr_wq; } ;
struct drm_i915_private {TYPE_1__ mm; int /*<<< orphan*/  mm_structs; int /*<<< orphan*/  mm_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int WQ_HIGHPRI ; 
 int WQ_UNBOUND ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int i915_gem_init_userptr(struct drm_i915_private *dev_priv)
{
	mutex_init(&dev_priv->mm_lock);
	hash_init(dev_priv->mm_structs);

	dev_priv->mm.userptr_wq =
		alloc_workqueue("i915-userptr-acquire",
				WQ_HIGHPRI | WQ_UNBOUND,
				0);
	if (!dev_priv->mm.userptr_wq)
		return -ENOMEM;

	return 0;
}