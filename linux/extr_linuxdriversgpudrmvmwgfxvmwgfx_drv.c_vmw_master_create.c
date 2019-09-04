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
struct vmw_master {int /*<<< orphan*/  lock; } ;
struct drm_master {struct vmw_master* driver_priv; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SIGTERM ; 
 struct vmw_master* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_lock_set_kill (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_master_init (struct vmw_master*) ; 

__attribute__((used)) static int vmw_master_create(struct drm_device *dev,
			     struct drm_master *master)
{
	struct vmw_master *vmaster;

	vmaster = kzalloc(sizeof(*vmaster), GFP_KERNEL);
	if (unlikely(!vmaster))
		return -ENOMEM;

	vmw_master_init(vmaster);
	ttm_lock_set_kill(&vmaster->lock, true, SIGTERM);
	master->driver_priv = vmaster;

	return 0;
}