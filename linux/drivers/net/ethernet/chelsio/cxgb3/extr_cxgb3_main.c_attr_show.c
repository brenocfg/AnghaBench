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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  stub1 (struct net_device*,char*) ; 
 struct net_device* to_net_dev (struct device*) ; 

__attribute__((used)) static ssize_t attr_show(struct device *d, char *buf,
			 ssize_t(*format) (struct net_device *, char *))
{
	ssize_t len;

	/* Synchronize with ioctls that may shut down the device */
	rtnl_lock();
	len = (*format) (to_net_dev(d), buf);
	rtnl_unlock();
	return len;
}