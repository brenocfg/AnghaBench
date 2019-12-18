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
struct ftgmac100 {scalar_t__ base; int /*<<< orphan*/  maht1; int /*<<< orphan*/  maht0; } ;

/* Variables and functions */
 scalar_t__ FTGMAC100_OFFSET_MAHT0 ; 
 scalar_t__ FTGMAC100_OFFSET_MAHT1 ; 
 int /*<<< orphan*/  ftgmac100_calc_mc_hash (struct ftgmac100*) ; 
 int /*<<< orphan*/  ftgmac100_start_hw (struct ftgmac100*) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 struct ftgmac100* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 

__attribute__((used)) static void ftgmac100_set_rx_mode(struct net_device *netdev)
{
	struct ftgmac100 *priv = netdev_priv(netdev);

	/* Setup the hash filter */
	ftgmac100_calc_mc_hash(priv);

	/* Interface down ? that's all there is to do */
	if (!netif_running(netdev))
		return;

	/* Update the HW */
	iowrite32(priv->maht0, priv->base + FTGMAC100_OFFSET_MAHT0);
	iowrite32(priv->maht1, priv->base + FTGMAC100_OFFSET_MAHT1);

	/* Reconfigure MACCR */
	ftgmac100_start_hw(priv);
}