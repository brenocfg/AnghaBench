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
struct viu_fh {TYPE_2__* dev; } ;
struct v4l2_input {scalar_t__ index; int /*<<< orphan*/  name; int /*<<< orphan*/  std; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;
struct TYPE_4__ {TYPE_1__* vdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  tvnorms; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int vidioc_enum_input(struct file *file, void *priv,
					struct v4l2_input *inp)
{
	struct viu_fh *fh = priv;

	if (inp->index != 0)
		return -EINVAL;

	inp->type = V4L2_INPUT_TYPE_CAMERA;
	inp->std = fh->dev->vdev->tvnorms;
	strscpy(inp->name, "Camera", sizeof(inp->name));
	return 0;
}