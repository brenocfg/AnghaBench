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
struct xmit_priv {int /*<<< orphan*/  xmit_tasklet; } ;
struct _adapter {int /*<<< orphan*/  pnetdev; scalar_t__ surprise_removed; scalar_t__ driver_stopped; struct xmit_priv xmitpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int r8712_xmitframe_complete (struct _adapter*,struct xmit_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 

void r8712_xmit_bh(void *priv)
{
	int ret = false;
	struct _adapter *padapter = priv;
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;

	if (padapter->driver_stopped ||
	    padapter->surprise_removed) {
		netdev_err(padapter->pnetdev, "xmit_bh => driver_stopped or surprise_removed\n");
		return;
	}
	ret = r8712_xmitframe_complete(padapter, pxmitpriv, NULL);
	if (!ret)
		return;
	tasklet_hi_schedule(&pxmitpriv->xmit_tasklet);
}