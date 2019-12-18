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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct ag71xx {int stop_desc_dma; struct net_device* ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_REG_RX_CTRL ; 
 int /*<<< orphan*/  AG71XX_REG_RX_DESC ; 
 int /*<<< orphan*/  AG71XX_REG_RX_STATUS ; 
 int /*<<< orphan*/  AG71XX_REG_TX_CTRL ; 
 int /*<<< orphan*/  AG71XX_REG_TX_DESC ; 
 int /*<<< orphan*/  AG71XX_REG_TX_STATUS ; 
 int RX_STATUS_BE ; 
 int RX_STATUS_OF ; 
 int RX_STATUS_PR ; 
 int TX_STATUS_BE ; 
 int TX_STATUS_PS ; 
 int TX_STATUS_UR ; 
 int /*<<< orphan*/  ag71xx_dma_wait_stop (struct ag71xx*) ; 
 int ag71xx_rr (struct ag71xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ag71xx_wr (struct ag71xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_err (struct ag71xx*,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 

__attribute__((used)) static void ag71xx_dma_reset(struct ag71xx *ag)
{
	struct net_device *ndev = ag->ndev;
	u32 val;
	int i;

	/* stop RX and TX */
	ag71xx_wr(ag, AG71XX_REG_RX_CTRL, 0);
	ag71xx_wr(ag, AG71XX_REG_TX_CTRL, 0);

	/* give the hardware some time to really stop all rx/tx activity
	 * clearing the descriptors too early causes random memory corruption
	 */
	ag71xx_dma_wait_stop(ag);

	/* clear descriptor addresses */
	ag71xx_wr(ag, AG71XX_REG_TX_DESC, ag->stop_desc_dma);
	ag71xx_wr(ag, AG71XX_REG_RX_DESC, ag->stop_desc_dma);

	/* clear pending RX/TX interrupts */
	for (i = 0; i < 256; i++) {
		ag71xx_wr(ag, AG71XX_REG_RX_STATUS, RX_STATUS_PR);
		ag71xx_wr(ag, AG71XX_REG_TX_STATUS, TX_STATUS_PS);
	}

	/* clear pending errors */
	ag71xx_wr(ag, AG71XX_REG_RX_STATUS, RX_STATUS_BE | RX_STATUS_OF);
	ag71xx_wr(ag, AG71XX_REG_TX_STATUS, TX_STATUS_BE | TX_STATUS_UR);

	val = ag71xx_rr(ag, AG71XX_REG_RX_STATUS);
	if (val)
		netif_err(ag, hw, ndev, "unable to clear DMA Rx status: %08x\n",
			  val);

	val = ag71xx_rr(ag, AG71XX_REG_TX_STATUS);

	/* mask out reserved bits */
	val &= ~0xff000000;

	if (val)
		netif_err(ag, hw, ndev, "unable to clear DMA Tx status: %08x\n",
			  val);
}