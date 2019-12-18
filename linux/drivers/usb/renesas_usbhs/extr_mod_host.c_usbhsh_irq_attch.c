#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * irq_attch; } ;
struct usbhsh_hpriv {TYPE_1__ mod; } ;
struct usbhs_priv {int dummy; } ;
struct usbhs_irq_state {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int USB_PORT_STAT_CONNECTION ; 
 int USB_PORT_STAT_C_CONNECTION ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  usbhs_irq_callback_update (struct usbhs_priv*,TYPE_1__*) ; 
 struct device* usbhs_priv_to_dev (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhsh_port_stat_set (struct usbhsh_hpriv*,int) ; 
 struct usbhsh_hpriv* usbhsh_priv_to_hpriv (struct usbhs_priv*) ; 

__attribute__((used)) static int usbhsh_irq_attch(struct usbhs_priv *priv,
			    struct usbhs_irq_state *irq_state)
{
	struct usbhsh_hpriv *hpriv = usbhsh_priv_to_hpriv(priv);
	struct device *dev = usbhs_priv_to_dev(priv);

	dev_dbg(dev, "device attached\n");

	usbhsh_port_stat_set(hpriv, USB_PORT_STAT_CONNECTION);
	usbhsh_port_stat_set(hpriv, USB_PORT_STAT_C_CONNECTION << 16);

	/*
	 * attch interrupt might happen infinitely on some device
	 * (on self power USB hub ?)
	 * disable it here.
	 *
	 * usbhsh_is_running() becomes effective
	 * according to this process.
	 * see
	 *	usbhsh_is_running()
	 *	usbhsh_urb_enqueue()
	 */
	hpriv->mod.irq_attch = NULL;
	usbhs_irq_callback_update(priv, &hpriv->mod);

	return 0;
}