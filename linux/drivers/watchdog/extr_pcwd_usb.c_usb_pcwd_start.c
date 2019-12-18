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
struct usb_pcwd_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ENABLE_WATCHDOG ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int usb_pcwd_send_command (struct usb_pcwd_private*,int /*<<< orphan*/ ,unsigned char*,unsigned char*) ; 

__attribute__((used)) static int usb_pcwd_start(struct usb_pcwd_private *usb_pcwd)
{
	unsigned char msb = 0x00;
	unsigned char lsb = 0x00;
	int retval;

	/* Enable Watchdog */
	retval = usb_pcwd_send_command(usb_pcwd, CMD_ENABLE_WATCHDOG,
								&msb, &lsb);

	if ((retval == 0) || (lsb == 0)) {
		pr_err("Card did not acknowledge enable attempt\n");
		return -1;
	}

	return 0;
}