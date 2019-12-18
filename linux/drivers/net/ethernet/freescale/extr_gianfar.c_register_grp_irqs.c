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
struct net_device {int dummy; } ;
struct gfar_private {int device_flags; struct net_device* ndev; } ;
struct gfar_priv_grp {struct gfar_private* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ER ; 
 int FSL_GIANFAR_DEV_HAS_MULTI_INTR ; 
 int /*<<< orphan*/  RX ; 
 int /*<<< orphan*/  TX ; 
 int /*<<< orphan*/  enable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct gfar_priv_grp*) ; 
 int /*<<< orphan*/  gfar_error ; 
 int /*<<< orphan*/  gfar_interrupt ; 
 TYPE_1__* gfar_irq (struct gfar_priv_grp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfar_receive ; 
 int /*<<< orphan*/  gfar_transmit ; 
 int /*<<< orphan*/  intr ; 
 int /*<<< orphan*/  netif_err (struct gfar_private*,int /*<<< orphan*/ ,struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfar_priv_grp*) ; 

__attribute__((used)) static int register_grp_irqs(struct gfar_priv_grp *grp)
{
	struct gfar_private *priv = grp->priv;
	struct net_device *dev = priv->ndev;
	int err;

	/* If the device has multiple interrupts, register for
	 * them.  Otherwise, only register for the one
	 */
	if (priv->device_flags & FSL_GIANFAR_DEV_HAS_MULTI_INTR) {
		/* Install our interrupt handlers for Error,
		 * Transmit, and Receive
		 */
		err = request_irq(gfar_irq(grp, ER)->irq, gfar_error, 0,
				  gfar_irq(grp, ER)->name, grp);
		if (err < 0) {
			netif_err(priv, intr, dev, "Can't get IRQ %d\n",
				  gfar_irq(grp, ER)->irq);

			goto err_irq_fail;
		}
		enable_irq_wake(gfar_irq(grp, ER)->irq);

		err = request_irq(gfar_irq(grp, TX)->irq, gfar_transmit, 0,
				  gfar_irq(grp, TX)->name, grp);
		if (err < 0) {
			netif_err(priv, intr, dev, "Can't get IRQ %d\n",
				  gfar_irq(grp, TX)->irq);
			goto tx_irq_fail;
		}
		err = request_irq(gfar_irq(grp, RX)->irq, gfar_receive, 0,
				  gfar_irq(grp, RX)->name, grp);
		if (err < 0) {
			netif_err(priv, intr, dev, "Can't get IRQ %d\n",
				  gfar_irq(grp, RX)->irq);
			goto rx_irq_fail;
		}
		enable_irq_wake(gfar_irq(grp, RX)->irq);

	} else {
		err = request_irq(gfar_irq(grp, TX)->irq, gfar_interrupt, 0,
				  gfar_irq(grp, TX)->name, grp);
		if (err < 0) {
			netif_err(priv, intr, dev, "Can't get IRQ %d\n",
				  gfar_irq(grp, TX)->irq);
			goto err_irq_fail;
		}
		enable_irq_wake(gfar_irq(grp, TX)->irq);
	}

	return 0;

rx_irq_fail:
	free_irq(gfar_irq(grp, TX)->irq, grp);
tx_irq_fail:
	free_irq(gfar_irq(grp, ER)->irq, grp);
err_irq_fail:
	return err;

}