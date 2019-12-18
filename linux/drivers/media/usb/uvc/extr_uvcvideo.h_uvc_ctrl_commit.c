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
struct v4l2_ext_control {int dummy; } ;
struct uvc_fh {int dummy; } ;

/* Variables and functions */
 int __uvc_ctrl_commit (struct uvc_fh*,int /*<<< orphan*/ ,struct v4l2_ext_control const*,unsigned int) ; 

__attribute__((used)) static inline int uvc_ctrl_commit(struct uvc_fh *handle,
				  const struct v4l2_ext_control *xctrls,
				  unsigned int xctrls_count)
{
	return __uvc_ctrl_commit(handle, 0, xctrls, xctrls_count);
}