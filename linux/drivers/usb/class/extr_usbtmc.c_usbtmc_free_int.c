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
struct usbtmc_device_data {int /*<<< orphan*/  kref; int /*<<< orphan*/ * iin_urb; int /*<<< orphan*/ * iin_buffer; int /*<<< orphan*/  iin_ep_present; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbtmc_delete ; 

__attribute__((used)) static void usbtmc_free_int(struct usbtmc_device_data *data)
{
	if (!data->iin_ep_present || !data->iin_urb)
		return;
	usb_kill_urb(data->iin_urb);
	kfree(data->iin_buffer);
	data->iin_buffer = NULL;
	usb_free_urb(data->iin_urb);
	data->iin_urb = NULL;
	kref_put(&data->kref, usbtmc_delete);
}