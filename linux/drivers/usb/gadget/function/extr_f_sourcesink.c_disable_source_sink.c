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
struct f_sourcesink {TYPE_2__ function; int /*<<< orphan*/  iso_out_ep; int /*<<< orphan*/  iso_in_ep; int /*<<< orphan*/  out_ep; int /*<<< orphan*/  in_ep; } ;
struct TYPE_3__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDBG (struct usb_composite_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_endpoints (struct usb_composite_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disable_source_sink(struct f_sourcesink *ss)
{
	struct usb_composite_dev	*cdev;

	cdev = ss->function.config->cdev;
	disable_endpoints(cdev, ss->in_ep, ss->out_ep, ss->iso_in_ep,
			ss->iso_out_ep);
	VDBG(cdev, "%s disabled\n", ss->function.name);
}