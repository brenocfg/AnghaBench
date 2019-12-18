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
typedef  int /*<<< orphan*/  u32 ;
struct hidpp_device {struct hid_device* hid_dev; } ;
struct hid_device {char const* uniq; int product; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dbg_hid (char*,char const*) ; 
 char* hidpp_unifying_get_name (struct hidpp_device*) ; 
 int hidpp_unifying_get_serial (struct hidpp_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 int /*<<< orphan*/  snprintf (char const*,int,char*,...) ; 

__attribute__((used)) static int hidpp_unifying_init(struct hidpp_device *hidpp)
{
	struct hid_device *hdev = hidpp->hid_dev;
	const char *name;
	u32 serial;
	int ret;

	ret = hidpp_unifying_get_serial(hidpp, &serial);
	if (ret)
		return ret;

	snprintf(hdev->uniq, sizeof(hdev->uniq), "%04x-%4phD",
		 hdev->product, &serial);
	dbg_hid("HID++ Unifying: Got serial: %s\n", hdev->uniq);

	name = hidpp_unifying_get_name(hidpp);
	if (!name)
		return -EIO;

	snprintf(hdev->name, sizeof(hdev->name), "%s", name);
	dbg_hid("HID++ Unifying: Got name: %s\n", name);

	kfree(name);
	return 0;
}