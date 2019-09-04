#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {long num_allocated; scalar_t__ pages_allocated; } ;
struct v3d_dev {int /*<<< orphan*/  bo_lock; TYPE_1__ bo_stats; } ;
struct seq_file {scalar_t__ private; } ;
struct drm_info_node {TYPE_2__* minor; } ;
struct drm_device {int dummy; } ;
struct TYPE_4__ {struct drm_device* dev; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,long) ; 
 struct v3d_dev* to_v3d_dev (struct drm_device*) ; 

__attribute__((used)) static int v3d_debugfs_bo_stats(struct seq_file *m, void *unused)
{
	struct drm_info_node *node = (struct drm_info_node *)m->private;
	struct drm_device *dev = node->minor->dev;
	struct v3d_dev *v3d = to_v3d_dev(dev);

	mutex_lock(&v3d->bo_lock);
	seq_printf(m, "allocated bos:          %d\n",
		   v3d->bo_stats.num_allocated);
	seq_printf(m, "allocated bo size (kb): %ld\n",
		   (long)v3d->bo_stats.pages_allocated << (PAGE_SHIFT - 10));
	mutex_unlock(&v3d->bo_lock);

	return 0;
}