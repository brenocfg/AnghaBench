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
struct v4l2_cropcap {scalar_t__ type; int /*<<< orphan*/  pixelaspect; } ;
struct file {int dummy; } ;
struct bttv_fh {struct bttv* btv; } ;
struct bttv {size_t tvnorm; } ;
struct TYPE_3__ {int /*<<< orphan*/  pixelaspect; } ;
struct TYPE_4__ {TYPE_1__ cropcap; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OVERLAY ; 
 TYPE_2__* bttv_tvnorms ; 

__attribute__((used)) static int bttv_cropcap(struct file *file, void *priv,
				struct v4l2_cropcap *cap)
{
	struct bttv_fh *fh = priv;
	struct bttv *btv = fh->btv;

	if (cap->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    cap->type != V4L2_BUF_TYPE_VIDEO_OVERLAY)
		return -EINVAL;

	/* defrect and bounds are set via g_selection */
	cap->pixelaspect = bttv_tvnorms[btv->tvnorm].cropcap.pixelaspect;

	return 0;
}