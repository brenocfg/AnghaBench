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
struct usb_otg {int /*<<< orphan*/  state; struct usb_bus* host; } ;
struct usb_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OTG_STATE_UNDEFINED ; 

__attribute__((used)) static int cpcap_usb_phy_set_host(struct usb_otg *otg, struct usb_bus *host)
{
	otg->host = host;
	if (!host)
		otg->state = OTG_STATE_UNDEFINED;

	return 0;
}