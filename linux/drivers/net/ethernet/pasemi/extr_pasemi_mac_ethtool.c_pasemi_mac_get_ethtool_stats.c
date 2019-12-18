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
typedef  int u64 ;
struct pasemi_mac {int /*<<< orphan*/  dma_if; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAS_DMA_RXINT_RCMDSTA (int /*<<< orphan*/ ) ; 
 int PAS_DMA_RXINT_RCMDSTA_DROPS_S ; 
 int /*<<< orphan*/  PAS_MAC_RMON (int) ; 
 struct pasemi_mac* netdev_priv (struct net_device*) ; 
 int pasemi_read_dma_reg (int /*<<< orphan*/ ) ; 
 int pasemi_read_mac_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pasemi_mac_get_ethtool_stats(struct net_device *netdev,
		struct ethtool_stats *stats, u64 *data)
{
	struct pasemi_mac *mac = netdev_priv(netdev);
	int i;

	data[0] = pasemi_read_dma_reg(PAS_DMA_RXINT_RCMDSTA(mac->dma_if))
			>> PAS_DMA_RXINT_RCMDSTA_DROPS_S;
	for (i = 0; i < 32; i++)
		data[1+i] = pasemi_read_mac_reg(mac->dma_if, PAS_MAC_RMON(i));
}