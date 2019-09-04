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
struct v4l2_streamparm {int dummy; } ;
struct soc_camera_host {TYPE_1__* ops; } ;
struct soc_camera_device {int /*<<< orphan*/  parent; } ;
struct file {struct soc_camera_device* private_data; } ;
struct TYPE_2__ {int (* set_parm ) (struct soc_camera_device*,struct v4l2_streamparm*) ;} ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 int stub1 (struct soc_camera_device*,struct v4l2_streamparm*) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int soc_camera_s_parm(struct file *file, void *fh,
			     struct v4l2_streamparm *a)
{
	struct soc_camera_device *icd = file->private_data;
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);

	if (ici->ops->set_parm)
		return ici->ops->set_parm(icd, a);

	return -ENOIOCTLCMD;
}