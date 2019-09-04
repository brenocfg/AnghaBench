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
struct video_device {int /*<<< orphan*/  entity; } ;
struct file {int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_pipeline_pm_use (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_fop_release (struct file*) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int video_release(struct file *file)
{
	struct video_device *vdev = video_devdata(file);

	vb2_fop_release(file);

	v4l2_pipeline_pm_use(&vdev->entity, 0);

	file->private_data = NULL;

	return 0;
}