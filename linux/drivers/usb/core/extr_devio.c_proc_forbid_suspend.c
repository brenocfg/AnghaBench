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
struct usb_dev_state {int suspend_allowed; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int usb_autoresume_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_forbid_suspend(struct usb_dev_state *ps)
{
	int ret = 0;

	if (ps->suspend_allowed) {
		ret = usb_autoresume_device(ps->dev);
		if (ret == 0)
			ps->suspend_allowed = false;
		else if (ret != -ENODEV)
			ret = -EIO;
	}
	return ret;
}