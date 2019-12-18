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
struct xenbus_device {int /*<<< orphan*/  devicetype; } ;
struct kobj_uevent_env {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ add_uevent_var (struct kobj_uevent_env*,char*,int /*<<< orphan*/ ) ; 
 struct xenbus_device* to_xenbus_device (struct device*) ; 

__attribute__((used)) static int xenbus_uevent_frontend(struct device *_dev,
				  struct kobj_uevent_env *env)
{
	struct xenbus_device *dev = to_xenbus_device(_dev);

	if (add_uevent_var(env, "MODALIAS=xen:%s", dev->devicetype))
		return -ENOMEM;

	return 0;
}