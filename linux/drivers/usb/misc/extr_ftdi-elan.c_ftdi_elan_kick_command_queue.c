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
struct usb_ftdi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ftdi_command_queue_work (struct usb_ftdi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ftdi_elan_kick_command_queue(struct usb_ftdi *ftdi)
{
	ftdi_command_queue_work(ftdi, 0);
}