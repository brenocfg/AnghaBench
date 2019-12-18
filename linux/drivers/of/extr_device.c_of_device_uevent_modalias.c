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
struct kobj_uevent_env {int buflen; int /*<<< orphan*/ * buf; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ add_uevent_var (struct kobj_uevent_env*,char*) ; 
 int of_device_get_modalias (struct device*,int /*<<< orphan*/ *,int) ; 

int of_device_uevent_modalias(struct device *dev, struct kobj_uevent_env *env)
{
	int sl;

	if ((!dev) || (!dev->of_node))
		return -ENODEV;

	/* Devicetree modalias is tricky, we add it in 2 steps */
	if (add_uevent_var(env, "MODALIAS="))
		return -ENOMEM;

	sl = of_device_get_modalias(dev, &env->buf[env->buflen-1],
				    sizeof(env->buf) - env->buflen);
	if (sl >= (sizeof(env->buf) - env->buflen))
		return -ENOMEM;
	env->buflen += sl;

	return 0;
}