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
struct ravb_private {int /*<<< orphan*/  emac_irq; int /*<<< orphan*/ * napi; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECMR ; 
 int /*<<< orphan*/  ECMR_MPDE ; 
 int /*<<< orphan*/  ECSIPR ; 
 int /*<<< orphan*/  ECSIPR_MPDIP ; 
 size_t RAVB_BE ; 
 size_t RAVB_NC ; 
 int /*<<< orphan*/  RIC0 ; 
 int /*<<< orphan*/  RIC2 ; 
 int /*<<< orphan*/  TIC ; 
 int enable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ravb_modify (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ravb_write (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ravb_wol_setup(struct net_device *ndev)
{
	struct ravb_private *priv = netdev_priv(ndev);

	/* Disable interrupts by clearing the interrupt masks. */
	ravb_write(ndev, 0, RIC0);
	ravb_write(ndev, 0, RIC2);
	ravb_write(ndev, 0, TIC);

	/* Only allow ECI interrupts */
	synchronize_irq(priv->emac_irq);
	napi_disable(&priv->napi[RAVB_NC]);
	napi_disable(&priv->napi[RAVB_BE]);
	ravb_write(ndev, ECSIPR_MPDIP, ECSIPR);

	/* Enable MagicPacket */
	ravb_modify(ndev, ECMR, ECMR_MPDE, ECMR_MPDE);

	return enable_irq_wake(priv->emac_irq);
}