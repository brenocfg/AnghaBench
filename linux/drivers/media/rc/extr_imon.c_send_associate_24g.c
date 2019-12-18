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
struct imon_context {int /*<<< orphan*/  usb_tx_buf; int /*<<< orphan*/  dev_present_intf0; } ;
typedef  int /*<<< orphan*/  packet ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int send_packet (struct imon_context*) ; 

__attribute__((used)) static int send_associate_24g(struct imon_context *ictx)
{
	int retval;
	const unsigned char packet[8] = { 0x01, 0x00, 0x00, 0x00,
					  0x00, 0x00, 0x00, 0x20 };

	if (!ictx) {
		pr_err("no context for device\n");
		return -ENODEV;
	}

	if (!ictx->dev_present_intf0) {
		pr_err("no iMON device present\n");
		return -ENODEV;
	}

	memcpy(ictx->usb_tx_buf, packet, sizeof(packet));
	retval = send_packet(ictx);

	return retval;
}