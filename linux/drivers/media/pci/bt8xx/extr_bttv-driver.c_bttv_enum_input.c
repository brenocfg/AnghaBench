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
struct v4l2_input {scalar_t__ index; int /*<<< orphan*/  std; int /*<<< orphan*/  status; int /*<<< orphan*/  name; scalar_t__ tuner; int /*<<< orphan*/  type; scalar_t__ audioset; } ;
struct file {int dummy; } ;
struct bttv_fh {struct bttv* btv; } ;
struct TYPE_3__ {size_t type; } ;
struct bttv {scalar_t__ tuner_type; scalar_t__ svhs; scalar_t__ input; TYPE_1__ c; } ;
typedef  int __u32 ;
struct TYPE_4__ {scalar_t__ video_inputs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_DSTATUS ; 
 int BT848_DSTATUS_HLOC ; 
 int BT848_DSTATUS_PRES ; 
 int /*<<< orphan*/  BTTV_NORMS ; 
 int EINVAL ; 
 scalar_t__ TUNER_ABSENT ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_TUNER ; 
 int /*<<< orphan*/  V4L2_IN_ST_NO_H_LOCK ; 
 int /*<<< orphan*/  V4L2_IN_ST_NO_SIGNAL ; 
 int btread (int /*<<< orphan*/ ) ; 
 TYPE_2__* bttv_tvcards ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int bttv_enum_input(struct file *file, void *priv,
					struct v4l2_input *i)
{
	struct bttv_fh *fh = priv;
	struct bttv *btv = fh->btv;

	if (i->index >= bttv_tvcards[btv->c.type].video_inputs)
		return -EINVAL;

	i->type     = V4L2_INPUT_TYPE_CAMERA;
	i->audioset = 0;

	if (btv->tuner_type != TUNER_ABSENT && i->index == 0) {
		sprintf(i->name, "Television");
		i->type  = V4L2_INPUT_TYPE_TUNER;
		i->tuner = 0;
	} else if (i->index == btv->svhs) {
		sprintf(i->name, "S-Video");
	} else {
		sprintf(i->name, "Composite%d", i->index);
	}

	if (i->index == btv->input) {
		__u32 dstatus = btread(BT848_DSTATUS);
		if (0 == (dstatus & BT848_DSTATUS_PRES))
			i->status |= V4L2_IN_ST_NO_SIGNAL;
		if (0 == (dstatus & BT848_DSTATUS_HLOC))
			i->status |= V4L2_IN_ST_NO_H_LOCK;
	}

	i->std = BTTV_NORMS;
	return 0;
}