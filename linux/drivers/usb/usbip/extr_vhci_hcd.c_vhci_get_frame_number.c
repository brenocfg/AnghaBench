#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* root_hub; } ;
struct usb_hcd {TYPE_2__ self; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int vhci_get_frame_number(struct usb_hcd *hcd)
{
	dev_err_ratelimited(&hcd->self.root_hub->dev, "Not yet implemented\n");
	return 0;
}