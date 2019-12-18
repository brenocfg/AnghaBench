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
struct slim_device {int /*<<< orphan*/  dev; } ;
struct kobj_uevent_env {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int add_uevent_var (struct kobj_uevent_env*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct slim_device* to_slim_device (struct device*) ; 

__attribute__((used)) static int slim_device_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct slim_device *sbdev = to_slim_device(dev);

	return add_uevent_var(env, "MODALIAS=slim:%s", dev_name(&sbdev->dev));
}