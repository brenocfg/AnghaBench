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
struct v4l2_selection {scalar_t__ type; } ;
struct soc_camera_host {TYPE_1__* ops; } ;
struct soc_camera_device {int /*<<< orphan*/  parent; } ;
struct file {struct soc_camera_device* private_data; } ;
struct TYPE_2__ {int (* get_selection ) (struct soc_camera_device*,struct v4l2_selection*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int stub1 (struct soc_camera_device*,struct v4l2_selection*) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int soc_camera_g_selection(struct file *file, void *fh,
				  struct v4l2_selection *s)
{
	struct soc_camera_device *icd = file->private_data;
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);

	/* With a wrong type no need to try to fall back to cropping */
	if (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	return ici->ops->get_selection(icd, s);
}