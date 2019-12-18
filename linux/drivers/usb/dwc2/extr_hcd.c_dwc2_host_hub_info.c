#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct urb {TYPE_3__* dev; } ;
struct dwc2_hsotg {int dummy; } ;
struct TYPE_6__ {int ttport; TYPE_2__* tt; } ;
struct TYPE_5__ {TYPE_1__* hub; } ;
struct TYPE_4__ {int devnum; } ;

/* Variables and functions */

__attribute__((used)) static void dwc2_host_hub_info(struct dwc2_hsotg *hsotg, void *context,
			       int *hub_addr, int *hub_port)
{
	struct urb *urb = context;

	if (urb->dev->tt)
		*hub_addr = urb->dev->tt->hub->devnum;
	else
		*hub_addr = 0;
	*hub_port = urb->dev->ttport;
}