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
struct lenovo_drvdata_tpkbd {int /*<<< orphan*/  led_mute; int /*<<< orphan*/  led_micmute; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct hid_device {TYPE_1__ dev; } ;

/* Variables and functions */
 struct lenovo_drvdata_tpkbd* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lenovo_attr_group_tpkbd ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lenovo_remove_tpkbd(struct hid_device *hdev)
{
	struct lenovo_drvdata_tpkbd *data_pointer = hid_get_drvdata(hdev);

	/*
	 * Only the trackpoint half of the keyboard has drvdata and stuff that
	 * needs unregistering.
	 */
	if (data_pointer == NULL)
		return;

	sysfs_remove_group(&hdev->dev.kobj,
			&lenovo_attr_group_tpkbd);

	led_classdev_unregister(&data_pointer->led_micmute);
	led_classdev_unregister(&data_pointer->led_mute);
}