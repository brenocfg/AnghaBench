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
struct usbtmc_file_data {scalar_t__ in_urbs_used; int /*<<< orphan*/  err_lock; scalar_t__ out_transfer_size; scalar_t__ out_status; scalar_t__ in_transfer_size; scalar_t__ in_status; int /*<<< orphan*/  in_anchor; int /*<<< orphan*/  submitted; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_scuttle_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int usbtmc_ioctl_cleanup_io(struct usbtmc_file_data *file_data)
{
	usb_kill_anchored_urbs(&file_data->submitted);
	usb_scuttle_anchored_urbs(&file_data->in_anchor);
	spin_lock_irq(&file_data->err_lock);
	file_data->in_status = 0;
	file_data->in_transfer_size = 0;
	file_data->out_status = 0;
	file_data->out_transfer_size = 0;
	spin_unlock_irq(&file_data->err_lock);

	file_data->in_urbs_used = 0;
	return 0;
}