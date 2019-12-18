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
struct i2c_hid {unsigned int bufsize; } ;
struct i2c_client {int /*<<< orphan*/  irq; } ;
struct hid_device {struct i2c_client* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  HID_INPUT_REPORT ; 
 unsigned int HID_MIN_BUFFER_SIZE ; 
 int /*<<< orphan*/  HID_OUTPUT_REPORT ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct i2c_hid* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_hid_alloc_buffers (struct i2c_hid*,unsigned int) ; 
 int /*<<< orphan*/  i2c_hid_find_max_report (struct hid_device*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  i2c_hid_free_buffers (struct i2c_hid*) ; 

__attribute__((used)) static int i2c_hid_start(struct hid_device *hid)
{
	struct i2c_client *client = hid->driver_data;
	struct i2c_hid *ihid = i2c_get_clientdata(client);
	int ret;
	unsigned int bufsize = HID_MIN_BUFFER_SIZE;

	i2c_hid_find_max_report(hid, HID_INPUT_REPORT, &bufsize);
	i2c_hid_find_max_report(hid, HID_OUTPUT_REPORT, &bufsize);
	i2c_hid_find_max_report(hid, HID_FEATURE_REPORT, &bufsize);

	if (bufsize > ihid->bufsize) {
		disable_irq(client->irq);
		i2c_hid_free_buffers(ihid);

		ret = i2c_hid_alloc_buffers(ihid, bufsize);
		enable_irq(client->irq);

		if (ret)
			return ret;
	}

	return 0;
}