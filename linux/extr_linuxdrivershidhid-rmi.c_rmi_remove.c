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
struct rmi_data {int device_flags; int /*<<< orphan*/  xport; int /*<<< orphan*/  reset_work; int /*<<< orphan*/  flags; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int RMI_DEVICE ; 
 int /*<<< orphan*/  RMI_STARTED ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct rmi_data* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int /*<<< orphan*/  rmi_unregister_transport_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rmi_remove(struct hid_device *hdev)
{
	struct rmi_data *hdata = hid_get_drvdata(hdev);

	if (hdata->device_flags & RMI_DEVICE) {
		clear_bit(RMI_STARTED, &hdata->flags);
		cancel_work_sync(&hdata->reset_work);
		rmi_unregister_transport_device(&hdata->xport);
	}

	hid_hw_stop(hdev);
}