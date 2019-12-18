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
struct pxa168_eth_private {int dummy; } ;
struct net_device {int /*<<< orphan*/  phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_CAUSE ; 
 int /*<<< orphan*/  INT_MASK ; 
 unsigned int PCR_EN ; 
 int /*<<< orphan*/  PORT_CONFIG ; 
 int /*<<< orphan*/  SDMA_CMD ; 
 unsigned int SDMA_CMD_ERD ; 
 int /*<<< orphan*/  abort_dma (struct pxa168_eth_private*) ; 
 struct pxa168_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 
 unsigned int rdl (struct pxa168_eth_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrl (struct pxa168_eth_private*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void eth_port_reset(struct net_device *dev)
{
	struct pxa168_eth_private *pep = netdev_priv(dev);
	unsigned int val = 0;

	/* Stop all interrupts for receive, transmit and error. */
	wrl(pep, INT_MASK, 0);

	/* Clear all interrupts */
	wrl(pep, INT_CAUSE, 0);

	/* Stop RX DMA */
	val = rdl(pep, SDMA_CMD);
	val &= ~SDMA_CMD_ERD;	/* abort dma command */

	/* Abort any transmit and receive operations and put DMA
	 * in idle state.
	 */
	abort_dma(pep);

	/* Disable port */
	val = rdl(pep, PORT_CONFIG);
	val &= ~PCR_EN;
	wrl(pep, PORT_CONFIG, val);

	phy_stop(dev->phydev);
}