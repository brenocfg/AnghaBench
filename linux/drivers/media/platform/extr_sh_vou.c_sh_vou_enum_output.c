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
struct v4l2_output {int /*<<< orphan*/  std; int /*<<< orphan*/  type; int /*<<< orphan*/  name; scalar_t__ index; } ;
struct TYPE_2__ {int /*<<< orphan*/  tvnorms; } ;
struct sh_vou_device {TYPE_1__ vdev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_OUTPUT_TYPE_ANALOG ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 struct sh_vou_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int sh_vou_enum_output(struct file *file, void *fh,
			      struct v4l2_output *a)
{
	struct sh_vou_device *vou_dev = video_drvdata(file);

	if (a->index)
		return -EINVAL;
	strscpy(a->name, "Video Out", sizeof(a->name));
	a->type = V4L2_OUTPUT_TYPE_ANALOG;
	a->std = vou_dev->vdev.tvnorms;
	return 0;
}