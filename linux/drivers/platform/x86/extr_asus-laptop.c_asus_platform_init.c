#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct asus_laptop {TYPE_2__* platform_device; } ;
struct TYPE_7__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_8__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_LAPTOP_FILE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  asus_attr_group ; 
 int platform_device_add (TYPE_2__*) ; 
 TYPE_2__* platform_device_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_device_del (TYPE_2__*) ; 
 int /*<<< orphan*/  platform_device_put (TYPE_2__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (TYPE_2__*,struct asus_laptop*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asus_platform_init(struct asus_laptop *asus)
{
	int result;

	asus->platform_device = platform_device_alloc(ASUS_LAPTOP_FILE, -1);
	if (!asus->platform_device)
		return -ENOMEM;
	platform_set_drvdata(asus->platform_device, asus);

	result = platform_device_add(asus->platform_device);
	if (result)
		goto fail_platform_device;

	result = sysfs_create_group(&asus->platform_device->dev.kobj,
				    &asus_attr_group);
	if (result)
		goto fail_sysfs;

	return 0;

fail_sysfs:
	platform_device_del(asus->platform_device);
fail_platform_device:
	platform_device_put(asus->platform_device);
	return result;
}