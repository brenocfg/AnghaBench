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
struct kobj_uevent_env {int dummy; } ;
struct hd_struct {TYPE_1__* info; scalar_t__* partno; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__* volname; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_uevent_var (struct kobj_uevent_env*,char*,scalar_t__*) ; 
 struct hd_struct* dev_to_part (struct device*) ; 

__attribute__((used)) static int part_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct hd_struct *part = dev_to_part(dev);

	add_uevent_var(env, "PARTN=%u", part->partno);
	if (part->info && part->info->volname[0])
		add_uevent_var(env, "PARTNAME=%s", part->info->volname);
	return 0;
}