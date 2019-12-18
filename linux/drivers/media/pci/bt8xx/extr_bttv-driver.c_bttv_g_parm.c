#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  timeperframe; int /*<<< orphan*/  readbuffers; } ;
struct TYPE_4__ {TYPE_2__ capture; } ;
struct v4l2_streamparm {scalar_t__ type; TYPE_1__ parm; } ;
struct file {int dummy; } ;
struct bttv_fh {struct bttv* btv; } ;
struct bttv {size_t tvnorm; } ;
struct TYPE_6__ {int /*<<< orphan*/  v4l2_id; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 TYPE_3__* bttv_tvnorms ; 
 int /*<<< orphan*/  gbuffers ; 
 int /*<<< orphan*/  v4l2_video_std_frame_period (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bttv_g_parm(struct file *file, void *f,
				struct v4l2_streamparm *parm)
{
	struct bttv_fh *fh = f;
	struct bttv *btv = fh->btv;

	if (parm->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;
	parm->parm.capture.readbuffers = gbuffers;
	v4l2_video_std_frame_period(bttv_tvnorms[btv->tvnorm].v4l2_id,
				    &parm->parm.capture.timeperframe);

	return 0;
}