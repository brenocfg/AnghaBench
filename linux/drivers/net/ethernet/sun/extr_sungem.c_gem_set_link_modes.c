#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct netdev_queue {int dummy; } ;
struct TYPE_6__ {scalar_t__ duplex; int speed; int pause; TYPE_2__* def; } ;
struct gem {scalar_t__ phy_type; int /*<<< orphan*/  dev; int /*<<< orphan*/  rx_pause_on; int /*<<< orphan*/  rx_pause_off; int /*<<< orphan*/  rx_fifo_sz; scalar_t__ regs; TYPE_3__ phy_mii; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {scalar_t__ (* read_link ) (TYPE_3__*) ;} ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ MAC_MCCFG ; 
 int MAC_MCCFG_RPE ; 
 int MAC_MCCFG_SPE ; 
 scalar_t__ MAC_RXCFG ; 
 int MAC_RXCFG_RCE ; 
 scalar_t__ MAC_STIME ; 
 scalar_t__ MAC_TXCFG ; 
 int MAC_TXCFG_EIPG0 ; 
 int MAC_TXCFG_ICOLL ; 
 int MAC_TXCFG_ICS ; 
 int MAC_TXCFG_NGU ; 
 int MAC_TXCFG_TCE ; 
 scalar_t__ MAC_XIFCFG ; 
 int MAC_XIFCFG_DISE ; 
 int MAC_XIFCFG_FLED ; 
 int MAC_XIFCFG_GMII ; 
 int MAC_XIFCFG_LLED ; 
 int MAC_XIFCFG_OE ; 
 int PCS_MIIADV_AP ; 
 int PCS_MIIADV_FD ; 
 int PCS_MIIADV_SP ; 
 scalar_t__ PCS_MIILP ; 
 int SPEED_10 ; 
 int SPEED_1000 ; 
 int /*<<< orphan*/  __netif_tx_lock (struct netdev_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __netif_tx_unlock (struct netdev_queue*) ; 
 scalar_t__ found_mii_phy (struct gem*) ; 
 int /*<<< orphan*/  gem_start_dma (struct gem*) ; 
 int /*<<< orphan*/  link ; 
 struct netdev_queue* netdev_get_tx_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  netif_info (struct gem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*) ; 
 scalar_t__ netif_msg_link (struct gem*) ; 
 scalar_t__ phy_mii_mdio0 ; 
 scalar_t__ phy_mii_mdio1 ; 
 scalar_t__ phy_serdes ; 
 scalar_t__ phy_serialink ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int gem_set_link_modes(struct gem *gp)
{
	struct netdev_queue *txq = netdev_get_tx_queue(gp->dev, 0);
	int full_duplex, speed, pause;
	u32 val;

	full_duplex = 0;
	speed = SPEED_10;
	pause = 0;

	if (found_mii_phy(gp)) {
	    	if (gp->phy_mii.def->ops->read_link(&gp->phy_mii))
	    		return 1;
		full_duplex = (gp->phy_mii.duplex == DUPLEX_FULL);
		speed = gp->phy_mii.speed;
		pause = gp->phy_mii.pause;
	} else if (gp->phy_type == phy_serialink ||
	    	   gp->phy_type == phy_serdes) {
		u32 pcs_lpa = readl(gp->regs + PCS_MIILP);

		if ((pcs_lpa & PCS_MIIADV_FD) || gp->phy_type == phy_serdes)
			full_duplex = 1;
		speed = SPEED_1000;
	}

	netif_info(gp, link, gp->dev, "Link is up at %d Mbps, %s-duplex\n",
		   speed, (full_duplex ? "full" : "half"));


	/* We take the tx queue lock to avoid collisions between
	 * this code, the tx path and the NAPI-driven error path
	 */
	__netif_tx_lock(txq, smp_processor_id());

	val = (MAC_TXCFG_EIPG0 | MAC_TXCFG_NGU);
	if (full_duplex) {
		val |= (MAC_TXCFG_ICS | MAC_TXCFG_ICOLL);
	} else {
		/* MAC_TXCFG_NBO must be zero. */
	}
	writel(val, gp->regs + MAC_TXCFG);

	val = (MAC_XIFCFG_OE | MAC_XIFCFG_LLED);
	if (!full_duplex &&
	    (gp->phy_type == phy_mii_mdio0 ||
	     gp->phy_type == phy_mii_mdio1)) {
		val |= MAC_XIFCFG_DISE;
	} else if (full_duplex) {
		val |= MAC_XIFCFG_FLED;
	}

	if (speed == SPEED_1000)
		val |= (MAC_XIFCFG_GMII);

	writel(val, gp->regs + MAC_XIFCFG);

	/* If gigabit and half-duplex, enable carrier extension
	 * mode.  Else, disable it.
	 */
	if (speed == SPEED_1000 && !full_duplex) {
		val = readl(gp->regs + MAC_TXCFG);
		writel(val | MAC_TXCFG_TCE, gp->regs + MAC_TXCFG);

		val = readl(gp->regs + MAC_RXCFG);
		writel(val | MAC_RXCFG_RCE, gp->regs + MAC_RXCFG);
	} else {
		val = readl(gp->regs + MAC_TXCFG);
		writel(val & ~MAC_TXCFG_TCE, gp->regs + MAC_TXCFG);

		val = readl(gp->regs + MAC_RXCFG);
		writel(val & ~MAC_RXCFG_RCE, gp->regs + MAC_RXCFG);
	}

	if (gp->phy_type == phy_serialink ||
	    gp->phy_type == phy_serdes) {
 		u32 pcs_lpa = readl(gp->regs + PCS_MIILP);

		if (pcs_lpa & (PCS_MIIADV_SP | PCS_MIIADV_AP))
			pause = 1;
	}

	if (!full_duplex)
		writel(512, gp->regs + MAC_STIME);
	else
		writel(64, gp->regs + MAC_STIME);
	val = readl(gp->regs + MAC_MCCFG);
	if (pause)
		val |= (MAC_MCCFG_SPE | MAC_MCCFG_RPE);
	else
		val &= ~(MAC_MCCFG_SPE | MAC_MCCFG_RPE);
	writel(val, gp->regs + MAC_MCCFG);

	gem_start_dma(gp);

	__netif_tx_unlock(txq);

	if (netif_msg_link(gp)) {
		if (pause) {
			netdev_info(gp->dev,
				    "Pause is enabled (rxfifo: %d off: %d on: %d)\n",
				    gp->rx_fifo_sz,
				    gp->rx_pause_off,
				    gp->rx_pause_on);
		} else {
			netdev_info(gp->dev, "Pause is disabled\n");
		}
	}

	return 0;
}