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
struct redrat3_dev {int wideband; int /*<<< orphan*/  dev; int /*<<< orphan*/  learn_urb; } ;
struct rc_dev {struct redrat3_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int redrat3_wideband_receiver(struct rc_dev *rcdev, int enable)
{
	struct redrat3_dev *rr3 = rcdev->priv;
	int ret = 0;

	rr3->wideband = enable != 0;

	if (enable) {
		ret = usb_submit_urb(rr3->learn_urb, GFP_KERNEL);
		if (ret)
			dev_err(rr3->dev, "Failed to submit learning urb: %d",
									ret);
	}

	return ret;
}