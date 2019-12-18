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
struct wrapper_priv_data {struct dwc2_hsotg* hsotg; } ;
struct usb_hcd {int /*<<< orphan*/  hcd_priv; } ;
struct dwc2_hsotg {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct dwc2_hsotg *dwc2_hcd_to_hsotg(struct usb_hcd *hcd)
{
	struct wrapper_priv_data *p;

	p = (struct wrapper_priv_data *)&hcd->hcd_priv;
	return p->hsotg;
}