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
struct urb {scalar_t__ status; int /*<<< orphan*/  actual_length; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  lbtf_deb_usb2 (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__) ; 

__attribute__((used)) static void if_usb_write_bulk_callback(struct urb *urb)
{
	if (urb->status != 0) {
		/* print the failure status number for debug */
		pr_info("URB in failure status: %d\n", urb->status);
	} else {
		lbtf_deb_usb2(&urb->dev->dev, "URB status is successful\n");
		lbtf_deb_usb2(&urb->dev->dev, "Actual length transmitted %d\n",
			     urb->actual_length);
	}
}