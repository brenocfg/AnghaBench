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
struct nfcmrvl_usb_drv_data {int /*<<< orphan*/  bulk_anchor; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfcmrvl_usb_stop_traffic(struct nfcmrvl_usb_drv_data *drv_data)
{
	usb_kill_anchored_urbs(&drv_data->bulk_anchor);
}