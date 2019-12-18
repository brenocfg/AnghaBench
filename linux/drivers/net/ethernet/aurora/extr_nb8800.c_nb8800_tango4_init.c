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
struct net_device {int dummy; } ;
struct nb8800_priv {int /*<<< orphan*/  rx_dma_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_ID ; 
 int /*<<< orphan*/  NB8800_RXC_CR ; 
 int /*<<< orphan*/  RCR_RFI (int) ; 
 int /*<<< orphan*/  nb8800_clearl (struct nb8800_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nb8800_tangox_init (struct net_device*) ; 
 struct nb8800_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int nb8800_tango4_init(struct net_device *dev)
{
	struct nb8800_priv *priv = netdev_priv(dev);
	int err;

	err = nb8800_tangox_init(dev);
	if (err)
		return err;

	/* On tango4 interrupt on DMA completion per frame works and gives
	 * better performance despite generating more rx interrupts.
	 */

	/* Disable unnecessary interrupt on rx completion */
	nb8800_clearl(priv, NB8800_RXC_CR, RCR_RFI(7));

	/* Request interrupt on descriptor DMA completion */
	priv->rx_dma_config |= DESC_ID;

	return 0;
}