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
struct gnss_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int add_uevent_var (struct kobj_uevent_env*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnss_type_name (struct gnss_device*) ; 
 struct gnss_device* to_gnss_device (struct device*) ; 

__attribute__((used)) static int gnss_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct gnss_device *gdev = to_gnss_device(dev);
	int ret;

	ret = add_uevent_var(env, "GNSS_TYPE=%s", gnss_type_name(gdev));
	if (ret)
		return ret;

	return 0;
}