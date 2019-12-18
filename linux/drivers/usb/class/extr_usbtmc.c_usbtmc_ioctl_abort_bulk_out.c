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
struct usbtmc_device_data {int /*<<< orphan*/  bTag_last_write; } ;

/* Variables and functions */
 int usbtmc_ioctl_abort_bulk_out_tag (struct usbtmc_device_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbtmc_ioctl_abort_bulk_out(struct usbtmc_device_data *data)
{
	return usbtmc_ioctl_abort_bulk_out_tag(data, data->bTag_last_write);
}