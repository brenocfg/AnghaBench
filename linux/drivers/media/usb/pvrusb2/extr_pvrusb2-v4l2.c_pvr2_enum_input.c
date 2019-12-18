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
typedef  int /*<<< orphan*/  tmp ;
struct v4l2_input {size_t index; scalar_t__* name; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_1__* mc_head; } ;
struct pvr2_v4l2_fh {size_t input_cnt; int* input_map; TYPE_2__ channel; } ;
struct pvr2_hdw {int dummy; } ;
struct pvr2_ctrl {int dummy; } ;
struct file {struct pvr2_v4l2_fh* private_data; } ;
struct TYPE_3__ {struct pvr2_hdw* hdw; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PVR2_CID_INPUT ; 
#define  PVR2_CVAL_INPUT_COMPOSITE 132 
#define  PVR2_CVAL_INPUT_DTV 131 
#define  PVR2_CVAL_INPUT_RADIO 130 
#define  PVR2_CVAL_INPUT_SVIDEO 129 
#define  PVR2_CVAL_INPUT_TV 128 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_TUNER ; 
 int /*<<< orphan*/  memset (struct v4l2_input*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pvr2_ctrl_get_valname (struct pvr2_ctrl*,int,scalar_t__*,int,unsigned int*) ; 
 struct pvr2_ctrl* pvr2_hdw_get_ctrl_by_id (struct pvr2_hdw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pvr2_enum_input(struct file *file, void *priv, struct v4l2_input *vi)
{
	struct pvr2_v4l2_fh *fh = file->private_data;
	struct pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	struct pvr2_ctrl *cptr;
	struct v4l2_input tmp;
	unsigned int cnt;
	int val;

	cptr = pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_INPUT);

	memset(&tmp, 0, sizeof(tmp));
	tmp.index = vi->index;
	if (vi->index >= fh->input_cnt)
		return -EINVAL;
	val = fh->input_map[vi->index];
	switch (val) {
	case PVR2_CVAL_INPUT_TV:
	case PVR2_CVAL_INPUT_DTV:
	case PVR2_CVAL_INPUT_RADIO:
		tmp.type = V4L2_INPUT_TYPE_TUNER;
		break;
	case PVR2_CVAL_INPUT_SVIDEO:
	case PVR2_CVAL_INPUT_COMPOSITE:
		tmp.type = V4L2_INPUT_TYPE_CAMERA;
		break;
	default:
		return -EINVAL;
	}

	cnt = 0;
	pvr2_ctrl_get_valname(cptr, val,
			tmp.name, sizeof(tmp.name) - 1, &cnt);
	tmp.name[cnt] = 0;

	/* Don't bother with audioset, since this driver currently
	   always switches the audio whenever the video is
	   switched. */

	/* Handling std is a tougher problem.  It doesn't make
	   sense in cases where a device might be multi-standard.
	   We could just copy out the current value for the
	   standard, but it can change over time.  For now just
	   leave it zero. */
	*vi = tmp;
	return 0;
}