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
struct ravb_private {scalar_t__ chip_id; int /*<<< orphan*/ * napi; int /*<<< orphan*/  emac_irq; int /*<<< orphan*/ * rx_irqs; int /*<<< orphan*/ * tx_irqs; struct platform_device* pdev; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 size_t RAVB_BE ; 
 size_t RAVB_NC ; 
 scalar_t__ RCAR_GEN2 ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  ravb_be_interrupt ; 
 int ravb_dmac_init (struct net_device*) ; 
 int /*<<< orphan*/  ravb_emac_init (struct net_device*) ; 
 int /*<<< orphan*/  ravb_emac_interrupt ; 
 int ravb_hook_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*,struct device*,char*) ; 
 int /*<<< orphan*/  ravb_interrupt ; 
 int /*<<< orphan*/  ravb_multi_interrupt ; 
 int /*<<< orphan*/  ravb_nc_interrupt ; 
 int ravb_phy_start (struct net_device*) ; 
 int /*<<< orphan*/  ravb_ptp_init (struct net_device*,struct platform_device*) ; 
 int /*<<< orphan*/  ravb_ptp_stop (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int ravb_open(struct net_device *ndev)
{
	struct ravb_private *priv = netdev_priv(ndev);
	struct platform_device *pdev = priv->pdev;
	struct device *dev = &pdev->dev;
	int error;

	napi_enable(&priv->napi[RAVB_BE]);
	napi_enable(&priv->napi[RAVB_NC]);

	if (priv->chip_id == RCAR_GEN2) {
		error = request_irq(ndev->irq, ravb_interrupt, IRQF_SHARED,
				    ndev->name, ndev);
		if (error) {
			netdev_err(ndev, "cannot request IRQ\n");
			goto out_napi_off;
		}
	} else {
		error = ravb_hook_irq(ndev->irq, ravb_multi_interrupt, ndev,
				      dev, "ch22:multi");
		if (error)
			goto out_napi_off;
		error = ravb_hook_irq(priv->emac_irq, ravb_emac_interrupt, ndev,
				      dev, "ch24:emac");
		if (error)
			goto out_free_irq;
		error = ravb_hook_irq(priv->rx_irqs[RAVB_BE], ravb_be_interrupt,
				      ndev, dev, "ch0:rx_be");
		if (error)
			goto out_free_irq_emac;
		error = ravb_hook_irq(priv->tx_irqs[RAVB_BE], ravb_be_interrupt,
				      ndev, dev, "ch18:tx_be");
		if (error)
			goto out_free_irq_be_rx;
		error = ravb_hook_irq(priv->rx_irqs[RAVB_NC], ravb_nc_interrupt,
				      ndev, dev, "ch1:rx_nc");
		if (error)
			goto out_free_irq_be_tx;
		error = ravb_hook_irq(priv->tx_irqs[RAVB_NC], ravb_nc_interrupt,
				      ndev, dev, "ch19:tx_nc");
		if (error)
			goto out_free_irq_nc_rx;
	}

	/* Device init */
	error = ravb_dmac_init(ndev);
	if (error)
		goto out_free_irq_nc_tx;
	ravb_emac_init(ndev);

	/* Initialise PTP Clock driver */
	if (priv->chip_id == RCAR_GEN2)
		ravb_ptp_init(ndev, priv->pdev);

	netif_tx_start_all_queues(ndev);

	/* PHY control start */
	error = ravb_phy_start(ndev);
	if (error)
		goto out_ptp_stop;

	return 0;

out_ptp_stop:
	/* Stop PTP Clock driver */
	if (priv->chip_id == RCAR_GEN2)
		ravb_ptp_stop(ndev);
out_free_irq_nc_tx:
	if (priv->chip_id == RCAR_GEN2)
		goto out_free_irq;
	free_irq(priv->tx_irqs[RAVB_NC], ndev);
out_free_irq_nc_rx:
	free_irq(priv->rx_irqs[RAVB_NC], ndev);
out_free_irq_be_tx:
	free_irq(priv->tx_irqs[RAVB_BE], ndev);
out_free_irq_be_rx:
	free_irq(priv->rx_irqs[RAVB_BE], ndev);
out_free_irq_emac:
	free_irq(priv->emac_irq, ndev);
out_free_irq:
	free_irq(ndev->irq, ndev);
out_napi_off:
	napi_disable(&priv->napi[RAVB_NC]);
	napi_disable(&priv->napi[RAVB_BE]);
	return error;
}