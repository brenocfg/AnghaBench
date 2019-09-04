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
struct vio_dev {int /*<<< orphan*/  compat; int /*<<< orphan*/  type; } ;
struct kobj_uevent_env {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_uevent_var (struct kobj_uevent_env*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vio_dev* to_vio_dev (struct device*) ; 

__attribute__((used)) static int vio_hotplug(struct device *dev, struct kobj_uevent_env *env)
{
	const struct vio_dev *vio_dev = to_vio_dev(dev);

	add_uevent_var(env, "MODALIAS=vio:T%sS%s", vio_dev->type, vio_dev->compat);
	return 0;
}