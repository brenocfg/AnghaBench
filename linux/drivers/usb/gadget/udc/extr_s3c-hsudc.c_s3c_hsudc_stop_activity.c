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
struct s3c_hsudc_ep {int stopped; } ;
struct TYPE_3__ {int /*<<< orphan*/  speed; } ;
struct s3c_hsudc {struct s3c_hsudc_ep* ep; TYPE_2__* pd; TYPE_1__ gadget; } ;
struct TYPE_4__ {int epnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESHUTDOWN ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  s3c_hsudc_nuke_ep (struct s3c_hsudc_ep*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s3c_hsudc_stop_activity(struct s3c_hsudc *hsudc)
{
	struct s3c_hsudc_ep *hsep;
	int epnum;

	hsudc->gadget.speed = USB_SPEED_UNKNOWN;

	for (epnum = 0; epnum < hsudc->pd->epnum; epnum++) {
		hsep = &hsudc->ep[epnum];
		hsep->stopped = 1;
		s3c_hsudc_nuke_ep(hsep, -ESHUTDOWN);
	}
}