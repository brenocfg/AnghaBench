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
struct v4l2_input {size_t index; int /*<<< orphan*/  name; scalar_t__ std; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;
struct ceu_subdev {TYPE_1__* v4l2_sd; } ;
struct ceu_device {size_t num_sd; struct ceu_subdev* subdevs; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,size_t,char*) ; 
 struct ceu_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int ceu_enum_input(struct file *file, void *priv,
			  struct v4l2_input *inp)
{
	struct ceu_device *ceudev = video_drvdata(file);
	struct ceu_subdev *ceusd;

	if (inp->index >= ceudev->num_sd)
		return -EINVAL;

	ceusd = &ceudev->subdevs[inp->index];

	inp->type = V4L2_INPUT_TYPE_CAMERA;
	inp->std = 0;
	snprintf(inp->name, sizeof(inp->name), "Camera%u: %s",
		 inp->index, ceusd->v4l2_sd->name);

	return 0;
}