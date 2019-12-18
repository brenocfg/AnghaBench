#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct v4l2_queryctrl {int dummy; } ;
struct uvc_video_chain {int dummy; } ;
struct uvc_fh {struct uvc_video_chain* chain; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int uvc_query_v4l2_ctrl (struct uvc_video_chain*,struct v4l2_queryctrl*) ; 

__attribute__((used)) static int uvc_ioctl_queryctrl(struct file *file, void *fh,
			       struct v4l2_queryctrl *qc)
{
	struct uvc_fh *handle = fh;
	struct uvc_video_chain *chain = handle->chain;

	return uvc_query_v4l2_ctrl(chain, qc);
}