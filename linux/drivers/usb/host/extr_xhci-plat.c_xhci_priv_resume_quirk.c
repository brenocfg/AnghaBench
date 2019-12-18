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
struct xhci_plat_priv {int (* resume_quirk ) (struct usb_hcd*) ;} ;
struct usb_hcd {int dummy; } ;

/* Variables and functions */
 struct xhci_plat_priv* hcd_to_xhci_priv (struct usb_hcd*) ; 
 int stub1 (struct usb_hcd*) ; 

__attribute__((used)) static int xhci_priv_resume_quirk(struct usb_hcd *hcd)
{
	struct xhci_plat_priv *priv = hcd_to_xhci_priv(hcd);

	if (!priv->resume_quirk)
		return 0;

	return priv->resume_quirk(hcd);
}