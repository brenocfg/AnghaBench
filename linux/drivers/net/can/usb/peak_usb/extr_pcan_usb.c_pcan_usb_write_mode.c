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
typedef  int /*<<< orphan*/  u8 ;
struct peak_usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCAN_USB_STARTUP_TIMEOUT ; 
 int /*<<< orphan*/  SJA1000_MODE_INIT ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int pcan_usb_set_bus (struct peak_usb_device*,int /*<<< orphan*/ ) ; 
 int pcan_usb_set_sja1000 (struct peak_usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcan_usb_write_mode(struct peak_usb_device *dev, u8 onoff)
{
	int err;

	err = pcan_usb_set_bus(dev, onoff);
	if (err)
		return err;

	if (!onoff) {
		err = pcan_usb_set_sja1000(dev, SJA1000_MODE_INIT);
	} else {
		/* the PCAN-USB needs time to init */
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_timeout(msecs_to_jiffies(PCAN_USB_STARTUP_TIMEOUT));
	}

	return err;
}