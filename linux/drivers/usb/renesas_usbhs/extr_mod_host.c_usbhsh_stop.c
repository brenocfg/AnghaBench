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
struct usbhsh_hpriv {int dummy; } ;
struct usbhs_priv {int dummy; } ;
struct usbhs_mod {int /*<<< orphan*/ * irq_sign; int /*<<< orphan*/ * irq_sack; int /*<<< orphan*/ * irq_dtch; int /*<<< orphan*/ * irq_attch; } ;
struct usb_hcd {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usbhs_irq_callback_update (struct usbhs_priv*,struct usbhs_mod*) ; 
 struct usbhs_mod* usbhs_mod_get_current (struct usbhs_priv*) ; 
 struct device* usbhs_priv_to_dev (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_sys_host_ctrl (struct usbhs_priv*,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usbhsh_hpriv_to_hcd (struct usbhsh_hpriv*) ; 
 struct usbhsh_hpriv* usbhsh_priv_to_hpriv (struct usbhs_priv*) ; 

__attribute__((used)) static int usbhsh_stop(struct usbhs_priv *priv)
{
	struct usbhsh_hpriv *hpriv = usbhsh_priv_to_hpriv(priv);
	struct usb_hcd *hcd = usbhsh_hpriv_to_hcd(hpriv);
	struct usbhs_mod *mod = usbhs_mod_get_current(priv);
	struct device *dev = usbhs_priv_to_dev(priv);

	/*
	 * disable irq callback
	 */
	mod->irq_attch	= NULL;
	mod->irq_dtch	= NULL;
	mod->irq_sack	= NULL;
	mod->irq_sign	= NULL;
	usbhs_irq_callback_update(priv, mod);

	usb_remove_hcd(hcd);

	/* disable sys */
	usbhs_sys_host_ctrl(priv, 0);

	dev_dbg(dev, "quit host\n");

	return 0;
}