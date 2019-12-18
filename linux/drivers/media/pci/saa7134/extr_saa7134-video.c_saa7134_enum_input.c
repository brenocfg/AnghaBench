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
struct v4l2_input {unsigned int index; int /*<<< orphan*/  std; int /*<<< orphan*/  status; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct saa7134_dev {unsigned int ctl_input; } ;
struct file {int dummy; } ;
struct TYPE_2__ {size_t type; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int SAA7134_INPUT_MAX ; 
#define  SAA7134_INPUT_TV 129 
#define  SAA7134_INPUT_TV_MONO 128 
 int /*<<< orphan*/  SAA7134_NORMS ; 
 size_t SAA7134_NO_INPUT ; 
 int /*<<< orphan*/  SAA7134_STATUS_VIDEO1 ; 
 int /*<<< orphan*/  SAA7134_STATUS_VIDEO2 ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_TUNER ; 
 int /*<<< orphan*/  V4L2_IN_ST_MACROVISION ; 
 int /*<<< orphan*/  V4L2_IN_ST_NO_H_LOCK ; 
 int /*<<< orphan*/  V4L2_IN_ST_NO_SIGNAL ; 
 TYPE_1__ card_in (struct saa7134_dev*,unsigned int) ; 
 int /*<<< orphan*/ * saa7134_input_name ; 
 int saa_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct saa7134_dev* video_drvdata (struct file*) ; 

int saa7134_enum_input(struct file *file, void *priv, struct v4l2_input *i)
{
	struct saa7134_dev *dev = video_drvdata(file);
	unsigned int n;

	n = i->index;
	if (n >= SAA7134_INPUT_MAX)
		return -EINVAL;
	if (card_in(dev, i->index).type == SAA7134_NO_INPUT)
		return -EINVAL;
	i->index = n;
	strscpy(i->name, saa7134_input_name[card_in(dev, n).type],
		sizeof(i->name));
	switch (card_in(dev, n).type) {
	case SAA7134_INPUT_TV:
	case SAA7134_INPUT_TV_MONO:
		i->type = V4L2_INPUT_TYPE_TUNER;
		break;
	default:
		i->type  = V4L2_INPUT_TYPE_CAMERA;
		break;
	}
	if (n == dev->ctl_input) {
		int v1 = saa_readb(SAA7134_STATUS_VIDEO1);
		int v2 = saa_readb(SAA7134_STATUS_VIDEO2);

		if (0 != (v1 & 0x40))
			i->status |= V4L2_IN_ST_NO_H_LOCK;
		if (0 != (v2 & 0x40))
			i->status |= V4L2_IN_ST_NO_SIGNAL;
		if (0 != (v2 & 0x0e))
			i->status |= V4L2_IN_ST_MACROVISION;
	}
	i->std = SAA7134_NORMS;
	return 0;
}