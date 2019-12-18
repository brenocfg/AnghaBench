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
struct v4l2_input {unsigned int index; int /*<<< orphan*/  std; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
struct tm6000_fh {struct tm6000_core* dev; } ;
struct tm6000_core {TYPE_1__* vinput; } ;
struct file {int dummy; } ;
struct TYPE_2__ {size_t type; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t TM6000_INPUT_TV ; 
 int /*<<< orphan*/  TM6000_STD ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_TUNER ; 
 int /*<<< orphan*/ * iname ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_enum_input(struct file *file, void *priv,
				struct v4l2_input *i)
{
	struct tm6000_fh   *fh = priv;
	struct tm6000_core *dev = fh->dev;
	unsigned int n;

	n = i->index;
	if (n >= 3)
		return -EINVAL;

	if (!dev->vinput[n].type)
		return -EINVAL;

	i->index = n;

	if (dev->vinput[n].type == TM6000_INPUT_TV)
		i->type = V4L2_INPUT_TYPE_TUNER;
	else
		i->type = V4L2_INPUT_TYPE_CAMERA;

	strscpy(i->name, iname[dev->vinput[n].type], sizeof(i->name));

	i->std = TM6000_STD;

	return 0;
}