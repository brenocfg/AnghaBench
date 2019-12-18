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
struct ftgmac100_rxdes {int rxdes0; } ;
struct ftgmac100 {size_t rx_pointer; struct ftgmac100_rxdes* rxdes; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTGMAC100_RXDES0_RXPKT_RDY ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ftgmac100_check_rx(struct ftgmac100 *priv)
{
	struct ftgmac100_rxdes *rxdes = &priv->rxdes[priv->rx_pointer];

	/* Do we have a packet ? */
	return !!(rxdes->rxdes0 & cpu_to_le32(FTGMAC100_RXDES0_RXPKT_RDY));
}