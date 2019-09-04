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
struct uvc_video_chain {int dummy; } ;
struct uvc_fh {struct uvc_video_chain* chain; } ;
struct file {int dummy; } ;

/* Variables and functions */
 long ENOTTY ; 
#define  UVCIOC_CTRL_MAP 129 
#define  UVCIOC_CTRL_QUERY 128 
 long uvc_ioctl_ctrl_map (struct uvc_video_chain*,void*) ; 
 long uvc_xu_ctrl_query (struct uvc_video_chain*,void*) ; 

__attribute__((used)) static long uvc_ioctl_default(struct file *file, void *fh, bool valid_prio,
			      unsigned int cmd, void *arg)
{
	struct uvc_fh *handle = fh;
	struct uvc_video_chain *chain = handle->chain;

	switch (cmd) {
	/* Dynamic controls. */
	case UVCIOC_CTRL_MAP:
		return uvc_ioctl_ctrl_map(chain, arg);

	case UVCIOC_CTRL_QUERY:
		return uvc_xu_ctrl_query(chain, arg);

	default:
		return -ENOTTY;
	}
}