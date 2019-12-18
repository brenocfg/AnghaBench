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
struct v4l2_ioctl_ops {int dummy; } ;
struct file {int f_flags; } ;

/* Variables and functions */
 int O_NONBLOCK ; 
 int v4l2_event_dequeue (void*,void*,int) ; 

__attribute__((used)) static int v4l_dqevent(const struct v4l2_ioctl_ops *ops,
				struct file *file, void *fh, void *arg)
{
	return v4l2_event_dequeue(fh, arg, file->f_flags & O_NONBLOCK);
}