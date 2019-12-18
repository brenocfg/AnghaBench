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
struct napi_struct {struct net_device* dev; } ;
struct arc_emac_priv {int dummy; } ;

/* Variables and functions */
 int RXINT_MASK ; 
 int /*<<< orphan*/  R_ENABLE ; 
 int TXINT_MASK ; 
 unsigned int arc_emac_rx (struct net_device*,int) ; 
 int /*<<< orphan*/  arc_emac_rx_miss_handle (struct net_device*) ; 
 int /*<<< orphan*/  arc_emac_rx_stall_check (struct net_device*,int,unsigned int) ; 
 int /*<<< orphan*/  arc_emac_tx_clean (struct net_device*) ; 
 int /*<<< orphan*/  arc_reg_or (struct arc_emac_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  napi_complete_done (struct napi_struct*,unsigned int) ; 
 struct arc_emac_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int arc_emac_poll(struct napi_struct *napi, int budget)
{
	struct net_device *ndev = napi->dev;
	struct arc_emac_priv *priv = netdev_priv(ndev);
	unsigned int work_done;

	arc_emac_tx_clean(ndev);
	arc_emac_rx_miss_handle(ndev);

	work_done = arc_emac_rx(ndev, budget);
	if (work_done < budget) {
		napi_complete_done(napi, work_done);
		arc_reg_or(priv, R_ENABLE, RXINT_MASK | TXINT_MASK);
	}

	arc_emac_rx_stall_check(ndev, budget, work_done);

	return work_done;
}