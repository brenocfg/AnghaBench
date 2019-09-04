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
struct kobject {int dummy; } ;
struct device {TYPE_1__* class; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_ownership ) (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 struct device* kobj_to_dev (struct kobject*) ; 
 int /*<<< orphan*/  stub1 (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void device_get_ownership(struct kobject *kobj, kuid_t *uid, kgid_t *gid)
{
	struct device *dev = kobj_to_dev(kobj);

	if (dev->class && dev->class->get_ownership)
		dev->class->get_ownership(dev, uid, gid);
}