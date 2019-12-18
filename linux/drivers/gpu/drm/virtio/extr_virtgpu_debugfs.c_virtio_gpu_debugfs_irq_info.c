#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_6__ {int /*<<< orphan*/  sync_seq; int /*<<< orphan*/  last_seq; } ;
struct virtio_gpu_device {TYPE_3__ fence_drv; } ;
struct seq_file {scalar_t__ private; } ;
struct drm_info_node {TYPE_2__* minor; } ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_4__ {struct virtio_gpu_device* dev_private; } ;

/* Variables and functions */
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
virtio_gpu_debugfs_irq_info(struct seq_file *m, void *data)
{
	struct drm_info_node *node = (struct drm_info_node *) m->private;
	struct virtio_gpu_device *vgdev = node->minor->dev->dev_private;

	seq_printf(m, "fence %llu %lld\n",
		   (u64)atomic64_read(&vgdev->fence_drv.last_seq),
		   vgdev->fence_drv.sync_seq);
	return 0;
}