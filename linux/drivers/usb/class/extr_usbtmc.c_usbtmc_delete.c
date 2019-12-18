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
struct usbtmc_device_data {int /*<<< orphan*/  usb_dev; } ;
struct kref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct usbtmc_device_data*) ; 
 struct usbtmc_device_data* to_usbtmc_data (struct kref*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usbtmc_delete(struct kref *kref)
{
	struct usbtmc_device_data *data = to_usbtmc_data(kref);

	usb_put_dev(data->usb_dev);
	kfree(data);
}