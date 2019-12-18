#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct watchdog_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* ioctl ) (struct watchdog_device*,unsigned int,unsigned long) ;} ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 int stub1 (struct watchdog_device*,unsigned int,unsigned long) ; 

__attribute__((used)) static int watchdog_ioctl_op(struct watchdog_device *wdd, unsigned int cmd,
							unsigned long arg)
{
	if (!wdd->ops->ioctl)
		return -ENOIOCTLCMD;

	return wdd->ops->ioctl(wdd, cmd, arg);
}