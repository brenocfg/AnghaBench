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
struct fec_enet_private {scalar_t__ hwp; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEC_DEFAULT_IMASK ; 
 scalar_t__ FEC_IMASK ; 
 int fec_enet_rx (struct net_device*,int) ; 
 int /*<<< orphan*/  fec_enet_tx (struct net_device*) ; 
 int /*<<< orphan*/  napi_complete_done (struct napi_struct*,int) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int fec_enet_rx_napi(struct napi_struct *napi, int budget)
{
	struct net_device *ndev = napi->dev;
	struct fec_enet_private *fep = netdev_priv(ndev);
	int pkts;

	pkts = fec_enet_rx(ndev, budget);

	fec_enet_tx(ndev);

	if (pkts < budget) {
		napi_complete_done(napi, pkts);
		writel(FEC_DEFAULT_IMASK, fep->hwp + FEC_IMASK);
	}
	return pkts;
}