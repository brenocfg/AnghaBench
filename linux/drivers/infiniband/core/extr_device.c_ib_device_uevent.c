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
struct kobj_uevent_env {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ add_uevent_var (struct kobj_uevent_env*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 

__attribute__((used)) static int ib_device_uevent(struct device *device,
			    struct kobj_uevent_env *env)
{
	if (add_uevent_var(env, "NAME=%s", dev_name(device)))
		return -ENOMEM;

	/*
	 * It would be nice to pass the node GUID with the event...
	 */

	return 0;
}