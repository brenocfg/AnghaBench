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
struct usbhs_priv {int /*<<< orphan*/  irqflags; int /*<<< orphan*/  irq; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_interrupt ; 
 int usbhs_mod_gadget_probe (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_mod_gadget_remove (struct usbhs_priv*) ; 
 int usbhs_mod_host_probe (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_mod_host_remove (struct usbhs_priv*) ; 
 struct device* usbhs_priv_to_dev (struct usbhs_priv*) ; 

int usbhs_mod_probe(struct usbhs_priv *priv)
{
	struct device *dev = usbhs_priv_to_dev(priv);
	int ret;

	/*
	 * install host/gadget driver
	 */
	ret = usbhs_mod_host_probe(priv);
	if (ret < 0)
		return ret;

	ret = usbhs_mod_gadget_probe(priv);
	if (ret < 0)
		goto mod_init_host_err;

	/* irq settings */
	ret = devm_request_irq(dev, priv->irq, usbhs_interrupt,
			  priv->irqflags, dev_name(dev), priv);
	if (ret) {
		dev_err(dev, "irq request err\n");
		goto mod_init_gadget_err;
	}

	return ret;

mod_init_gadget_err:
	usbhs_mod_gadget_remove(priv);
mod_init_host_err:
	usbhs_mod_host_remove(priv);

	return ret;
}