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
struct ishtp_hid_data {int request_done; int /*<<< orphan*/  hid_wait; } ;
struct hid_device {struct ishtp_hid_data* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void ishtp_hid_wakeup(struct hid_device *hid)
{
	struct ishtp_hid_data *hid_data = hid->driver_data;

	hid_data->request_done = true;
	wake_up_interruptible(&hid_data->hid_wait);
}