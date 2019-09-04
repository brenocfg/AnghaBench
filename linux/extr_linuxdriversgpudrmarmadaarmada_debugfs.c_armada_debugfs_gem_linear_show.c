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
struct seq_file {struct drm_info_node* private; } ;
struct drm_printer {int dummy; } ;
struct drm_info_node {TYPE_1__* minor; } ;
struct drm_device {struct armada_private* dev_private; } ;
struct armada_private {int /*<<< orphan*/  linear_lock; int /*<<< orphan*/  linear; } ;
struct TYPE_2__ {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mm_print (int /*<<< orphan*/ *,struct drm_printer*) ; 
 struct drm_printer drm_seq_file_printer (struct seq_file*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int armada_debugfs_gem_linear_show(struct seq_file *m, void *data)
{
	struct drm_info_node *node = m->private;
	struct drm_device *dev = node->minor->dev;
	struct armada_private *priv = dev->dev_private;
	struct drm_printer p = drm_seq_file_printer(m);

	mutex_lock(&priv->linear_lock);
	drm_mm_print(&priv->linear, &p);
	mutex_unlock(&priv->linear_lock);

	return 0;
}