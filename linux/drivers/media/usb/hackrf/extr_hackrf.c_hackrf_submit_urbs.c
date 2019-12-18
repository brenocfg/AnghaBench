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
struct hackrf_dev {int urbs_initialized; int /*<<< orphan*/  urbs_submitted; int /*<<< orphan*/  dev; int /*<<< orphan*/ * urb_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hackrf_kill_urbs (struct hackrf_dev*) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hackrf_submit_urbs(struct hackrf_dev *dev)
{
	int i, ret;

	for (i = 0; i < dev->urbs_initialized; i++) {
		dev_dbg(dev->dev, "submit urb=%d\n", i);
		ret = usb_submit_urb(dev->urb_list[i], GFP_KERNEL);
		if (ret) {
			dev_err(dev->dev, "Could not submit URB no. %d - get them all back\n",
					i);
			hackrf_kill_urbs(dev);
			return ret;
		}
		dev->urbs_submitted++;
	}

	return 0;
}