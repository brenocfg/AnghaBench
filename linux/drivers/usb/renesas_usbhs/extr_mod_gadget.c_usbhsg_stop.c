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
struct usbhsg_gpriv {int /*<<< orphan*/  gadget; TYPE_1__* driver; } ;
struct usbhs_priv {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disconnect ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  USBHSG_STATUS_STARTED ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 struct usbhsg_gpriv* usbhsg_priv_to_gpriv (struct usbhs_priv*) ; 
 int usbhsg_try_stop (struct usbhs_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbhsg_stop(struct usbhs_priv *priv)
{
	struct usbhsg_gpriv *gpriv = usbhsg_priv_to_gpriv(priv);

	/* cable disconnect */
	if (gpriv->driver &&
	    gpriv->driver->disconnect)
		gpriv->driver->disconnect(&gpriv->gadget);

	return usbhsg_try_stop(priv, USBHSG_STATUS_STARTED);
}