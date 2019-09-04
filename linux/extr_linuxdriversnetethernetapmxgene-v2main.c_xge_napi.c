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
struct xge_pdata {int dummy; } ;
struct net_device {int dummy; } ;
struct napi_struct {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_complete_done (struct napi_struct*,int) ; 
 struct xge_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  xge_intr_enable (struct xge_pdata*) ; 
 int xge_rx_poll (struct net_device*,int const) ; 
 int /*<<< orphan*/  xge_txc_poll (struct net_device*) ; 

__attribute__((used)) static int xge_napi(struct napi_struct *napi, const int budget)
{
	struct net_device *ndev = napi->dev;
	struct xge_pdata *pdata;
	int processed;

	pdata = netdev_priv(ndev);

	xge_txc_poll(ndev);
	processed = xge_rx_poll(ndev, budget);

	if (processed < budget) {
		napi_complete_done(napi, processed);
		xge_intr_enable(pdata);
	}

	return processed;
}