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
struct v4l2_ext_controls {int dummy; } ;
struct uvc_fh {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int uvc_ioctl_s_try_ext_ctrls (struct uvc_fh*,struct v4l2_ext_controls*,int) ; 

__attribute__((used)) static int uvc_ioctl_try_ext_ctrls(struct file *file, void *fh,
				   struct v4l2_ext_controls *ctrls)
{
	struct uvc_fh *handle = fh;

	return uvc_ioctl_s_try_ext_ctrls(handle, ctrls, false);
}