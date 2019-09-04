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
struct hidpp_device {int /*<<< orphan*/  protocol_minor; int /*<<< orphan*/  protocol_major; int /*<<< orphan*/  hid_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hid_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hidpp_root_get_protocol_version (struct hidpp_device*) ; 

__attribute__((used)) static bool hidpp_is_connected(struct hidpp_device *hidpp)
{
	int ret;

	ret = hidpp_root_get_protocol_version(hidpp);
	if (!ret)
		hid_dbg(hidpp->hid_dev, "HID++ %u.%u device connected.\n",
			hidpp->protocol_major, hidpp->protocol_minor);
	return ret == 0;
}