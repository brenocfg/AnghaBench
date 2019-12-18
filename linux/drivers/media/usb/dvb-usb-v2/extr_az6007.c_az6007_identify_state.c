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
struct dvb_usb_device {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AZ6007_READ_DATA ; 
 int COLD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int WARM ; 
 int __az6007_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  __az6007_write (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static int az6007_identify_state(struct dvb_usb_device *d, const char **name)
{
	int ret;
	u8 *mac;

	pr_debug("Identifying az6007 state\n");

	mac = kmalloc(6, GFP_ATOMIC);
	if (!mac)
		return -ENOMEM;

	/* Try to read the mac address */
	ret = __az6007_read(d->udev, AZ6007_READ_DATA, 6, 0, mac, 6);
	if (ret == 6)
		ret = WARM;
	else
		ret = COLD;

	kfree(mac);

	if (ret == COLD) {
		__az6007_write(d->udev, 0x09, 1, 0, NULL, 0);
		__az6007_write(d->udev, 0x00, 0, 0, NULL, 0);
		__az6007_write(d->udev, 0x00, 0, 0, NULL, 0);
	}

	pr_debug("Device is on %s state\n",
		 ret == WARM ? "warm" : "cold");
	return ret;
}