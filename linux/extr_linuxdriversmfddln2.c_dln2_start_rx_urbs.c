#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dln2_dev {int /*<<< orphan*/ * rx_urb; TYPE_1__* interface; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int DLN2_MAX_URBS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dln2_start_rx_urbs(struct dln2_dev *dln2, gfp_t gfp)
{
	struct device *dev = &dln2->interface->dev;
	int ret;
	int i;

	for (i = 0; i < DLN2_MAX_URBS; i++) {
		ret = usb_submit_urb(dln2->rx_urb[i], gfp);
		if (ret < 0) {
			dev_err(dev, "failed to submit RX URB: %d\n", ret);
			return ret;
		}
	}

	return 0;
}