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
struct amba_device {int /*<<< orphan*/  periphid; } ;

/* Variables and functions */
 int add_uevent_var (struct kobj_uevent_env*,char*,int /*<<< orphan*/ ) ; 
 struct amba_device* to_amba_device (struct device*) ; 

__attribute__((used)) static int amba_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct amba_device *pcdev = to_amba_device(dev);
	int retval = 0;

	retval = add_uevent_var(env, "AMBA_ID=%08x", pcdev->periphid);
	if (retval)
		return retval;

	retval = add_uevent_var(env, "MODALIAS=amba:d%08X", pcdev->periphid);
	return retval;
}