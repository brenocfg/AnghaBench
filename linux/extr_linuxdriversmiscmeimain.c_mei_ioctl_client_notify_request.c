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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct mei_cl {int dummy; } ;
struct file {struct mei_cl* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MEI_HBM_NOTIFICATION_START ; 
 scalar_t__ MEI_HBM_NOTIFICATION_STOP ; 
 int mei_cl_notify_request (struct mei_cl*,struct file const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mei_ioctl_client_notify_request(const struct file *file, u32 request)
{
	struct mei_cl *cl = file->private_data;

	if (request != MEI_HBM_NOTIFICATION_START &&
	    request != MEI_HBM_NOTIFICATION_STOP)
		return -EINVAL;

	return mei_cl_notify_request(cl, file, (u8)request);
}