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
struct usbhsh_hpriv {int /*<<< orphan*/  setup_ack_done; } ;
struct usbhs_priv {int dummy; } ;
struct usbhs_irq_state {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct device* usbhs_priv_to_dev (struct usbhs_priv*) ; 
 struct usbhsh_hpriv* usbhsh_priv_to_hpriv (struct usbhs_priv*) ; 

__attribute__((used)) static int usbhsh_irq_setup_err(struct usbhs_priv *priv,
				struct usbhs_irq_state *irq_state)
{
	struct usbhsh_hpriv *hpriv = usbhsh_priv_to_hpriv(priv);
	struct device *dev = usbhs_priv_to_dev(priv);

	dev_dbg(dev, "setup packet Err\n");

	complete(&hpriv->setup_ack_done); /* see usbhsh_urb_enqueue() */

	return 0;
}