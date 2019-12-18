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
struct v4l2_input {scalar_t__ index; int /*<<< orphan*/  name; int /*<<< orphan*/  std; int /*<<< orphan*/  type; } ;
struct soc_camera_device {TYPE_1__* vdev; } ;
struct file {struct soc_camera_device* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  tvnorms; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int soc_camera_enum_input(struct file *file, void *priv,
				 struct v4l2_input *inp)
{
	struct soc_camera_device *icd = file->private_data;

	if (inp->index != 0)
		return -EINVAL;

	/* default is camera */
	inp->type = V4L2_INPUT_TYPE_CAMERA;
	inp->std = icd->vdev->tvnorms;
	strscpy(inp->name, "Camera", sizeof(inp->name));

	return 0;
}