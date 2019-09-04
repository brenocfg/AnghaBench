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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct hid_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntrig_attribute_group ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ntrig_remove(struct hid_device *hdev)
{
	sysfs_remove_group(&hdev->dev.kobj,
			   &ntrig_attribute_group);
	hid_hw_stop(hdev);
	kfree(hid_get_drvdata(hdev));
}