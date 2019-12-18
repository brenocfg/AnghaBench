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
struct hidpp_ff_private_data {int /*<<< orphan*/  effect_ids; int /*<<< orphan*/  wq; TYPE_1__* hidpp; } ;
struct hid_device {int /*<<< orphan*/  dev; } ;
struct ff_device {struct hidpp_ff_private_data* private; } ;
struct TYPE_2__ {struct hid_device* hid_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_attr_range ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_info (struct hid_device*,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hidpp_ff_destroy(struct ff_device *ff)
{
	struct hidpp_ff_private_data *data = ff->private;
	struct hid_device *hid = data->hidpp->hid_dev;

	hid_info(hid, "Unloading HID++ force feedback.\n");

	device_remove_file(&hid->dev, &dev_attr_range);
	destroy_workqueue(data->wq);
	kfree(data->effect_ids);
}