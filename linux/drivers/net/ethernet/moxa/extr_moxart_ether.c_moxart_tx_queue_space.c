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
struct moxart_mac_priv_t {int /*<<< orphan*/  tx_tail; int /*<<< orphan*/  tx_head; } ;

/* Variables and functions */
 int CIRC_SPACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_DESC_NUM ; 
 struct moxart_mac_priv_t* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int moxart_tx_queue_space(struct net_device *ndev)
{
	struct moxart_mac_priv_t *priv = netdev_priv(ndev);

	return CIRC_SPACE(priv->tx_head, priv->tx_tail, TX_DESC_NUM);
}