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
struct btusb_data {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTUSB_BOOTLOADER ; 
 int btusb_recv_bulk (struct btusb_data*,void*,int) ; 
 int btusb_recv_intr (struct btusb_data*,void*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btusb_recv_bulk_intel(struct btusb_data *data, void *buffer,
				 int count)
{
	/* When the device is in bootloader mode, then it can send
	 * events via the bulk endpoint. These events are treated the
	 * same way as the ones received from the interrupt endpoint.
	 */
	if (test_bit(BTUSB_BOOTLOADER, &data->flags))
		return btusb_recv_intr(data, buffer, count);

	return btusb_recv_bulk(data, buffer, count);
}