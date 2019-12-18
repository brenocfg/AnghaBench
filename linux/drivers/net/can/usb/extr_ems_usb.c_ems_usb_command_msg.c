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
struct ems_usb {int /*<<< orphan*/ * tx_msg_buffer; int /*<<< orphan*/  udev; } ;
struct ems_cpc_msg {scalar_t__ length; } ;

/* Variables and functions */
 size_t CPC_HEADER_SIZE ; 
 scalar_t__ CPC_MSG_HEADER_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ems_cpc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ems_usb_command_msg(struct ems_usb *dev, struct ems_cpc_msg *msg)
{
	int actual_length;

	/* Copy payload */
	memcpy(&dev->tx_msg_buffer[CPC_HEADER_SIZE], msg,
	       msg->length + CPC_MSG_HEADER_LEN);

	/* Clear header */
	memset(&dev->tx_msg_buffer[0], 0, CPC_HEADER_SIZE);

	return usb_bulk_msg(dev->udev, usb_sndbulkpipe(dev->udev, 2),
			    &dev->tx_msg_buffer[0],
			    msg->length + CPC_MSG_HEADER_LEN + CPC_HEADER_SIZE,
			    &actual_length, 1000);
}