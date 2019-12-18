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
struct go7007_usb {int /*<<< orphan*/  intr_urb; } ;
struct go7007 {int /*<<< orphan*/  dev; struct go7007_usb* hpi_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int go7007_usb_read_interrupt(struct go7007 *go)
{
	struct go7007_usb *usb = go->hpi_context;
	int r;

	r = usb_submit_urb(usb->intr_urb, GFP_KERNEL);
	if (r < 0) {
		dev_err(go->dev, "unable to submit interrupt urb: %d\n", r);
		return r;
	}
	return 0;
}