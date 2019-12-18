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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  child_relid; } ;
struct kobject {int /*<<< orphan*/  kset; } ;
struct vmbus_channel {TYPE_1__ offermsg; struct kobject kobj; } ;
struct device {int dummy; } ;
struct hv_device {int /*<<< orphan*/  channels_kset; struct device device; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_ADD ; 
 int /*<<< orphan*/  dev_err (struct device const*,char*) ; 
 int kobject_init_and_add (struct kobject*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_uevent (struct kobject*,int /*<<< orphan*/ ) ; 
 int sysfs_create_group (struct kobject*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_chan_group ; 
 int /*<<< orphan*/  vmbus_chan_ktype ; 

int vmbus_add_channel_kobj(struct hv_device *dev, struct vmbus_channel *channel)
{
	const struct device *device = &dev->device;
	struct kobject *kobj = &channel->kobj;
	u32 relid = channel->offermsg.child_relid;
	int ret;

	kobj->kset = dev->channels_kset;
	ret = kobject_init_and_add(kobj, &vmbus_chan_ktype, NULL,
				   "%u", relid);
	if (ret)
		return ret;

	ret = sysfs_create_group(kobj, &vmbus_chan_group);

	if (ret) {
		/*
		 * The calling functions' error handling paths will cleanup the
		 * empty channel directory.
		 */
		dev_err(device, "Unable to set up channel sysfs files\n");
		return ret;
	}

	kobject_uevent(kobj, KOBJ_ADD);

	return 0;
}