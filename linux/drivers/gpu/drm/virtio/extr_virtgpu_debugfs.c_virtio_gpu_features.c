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
struct virtio_gpu_device {int /*<<< orphan*/  num_scanouts; int /*<<< orphan*/  num_capsets; int /*<<< orphan*/  has_edid; int /*<<< orphan*/  has_virgl_3d; } ;
struct seq_file {scalar_t__ private; } ;
struct drm_info_node {TYPE_2__* minor; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {struct virtio_gpu_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  virtio_add_bool (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_add_int (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int virtio_gpu_features(struct seq_file *m, void *data)
{
	struct drm_info_node *node = (struct drm_info_node *) m->private;
	struct virtio_gpu_device *vgdev = node->minor->dev->dev_private;

	virtio_add_bool(m, "virgl", vgdev->has_virgl_3d);
	virtio_add_bool(m, "edid", vgdev->has_edid);
	virtio_add_int(m, "cap sets", vgdev->num_capsets);
	virtio_add_int(m, "scanouts", vgdev->num_scanouts);
	return 0;
}