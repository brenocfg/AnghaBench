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
typedef  scalar_t__ u8 ;
struct usb_interface {int /*<<< orphan*/  usb_dev; } ;
struct tty_dev {struct mux_dev* priv_dev; } ;
struct mux_dev {scalar_t__ usb_state; int /*<<< orphan*/  rx_cb; } ;

/* Variables and functions */
 scalar_t__ MAX_ISSUE_NUM ; 
 scalar_t__ PM_NORMAL ; 
 scalar_t__ PM_SUSPEND ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdm_mux_recv (struct mux_dev*,int /*<<< orphan*/ ) ; 
 struct tty_dev* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int gdm_mux_resume(struct usb_interface *intf)
{
	struct tty_dev *tty_dev;
	struct mux_dev *mux_dev;
	u8 i;

	tty_dev = usb_get_intfdata(intf);
	mux_dev = tty_dev->priv_dev;

	if (mux_dev->usb_state != PM_SUSPEND) {
		dev_err(intf->usb_dev, "usb resume - invalid state\n");
		return -1;
	}

	mux_dev->usb_state = PM_NORMAL;

	for (i = 0; i < MAX_ISSUE_NUM; i++)
		gdm_mux_recv(mux_dev, mux_dev->rx_cb);

	return 0;
}