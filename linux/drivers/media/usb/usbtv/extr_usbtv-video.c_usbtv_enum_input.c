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
struct v4l2_input {int index; int /*<<< orphan*/  std; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  tvnorms; } ;
struct usbtv {TYPE_1__ vdev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  USBTV_COMPOSITE_INPUT 129 
#define  USBTV_SVIDEO_INPUT 128 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 struct usbtv* video_drvdata (struct file*) ; 

__attribute__((used)) static int usbtv_enum_input(struct file *file, void *priv,
					struct v4l2_input *i)
{
	struct usbtv *dev = video_drvdata(file);

	switch (i->index) {
	case USBTV_COMPOSITE_INPUT:
		strscpy(i->name, "Composite", sizeof(i->name));
		break;
	case USBTV_SVIDEO_INPUT:
		strscpy(i->name, "S-Video", sizeof(i->name));
		break;
	default:
		return -EINVAL;
	}

	i->type = V4L2_INPUT_TYPE_CAMERA;
	i->std = dev->vdev.tvnorms;
	return 0;
}