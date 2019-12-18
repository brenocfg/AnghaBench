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
struct usb_composite_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; TYPE_1__* config; } ;
struct f_loopback {TYPE_2__ function; int /*<<< orphan*/  out_ep; int /*<<< orphan*/  in_ep; } ;
struct TYPE_3__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDBG (struct usb_composite_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_endpoints (struct usb_composite_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void disable_loopback(struct f_loopback *loop)
{
	struct usb_composite_dev	*cdev;

	cdev = loop->function.config->cdev;
	disable_endpoints(cdev, loop->in_ep, loop->out_ep, NULL, NULL);
	VDBG(cdev, "%s disabled\n", loop->function.name);
}