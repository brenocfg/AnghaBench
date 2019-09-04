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
struct xge_pdata {int /*<<< orphan*/  nbufs; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUM_BUFS ; 
 struct xge_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  xge_port_init (struct net_device*) ; 
 int xge_port_reset (struct net_device*) ; 

__attribute__((used)) static int xge_init_hw(struct net_device *ndev)
{
	struct xge_pdata *pdata = netdev_priv(ndev);
	int ret;

	ret = xge_port_reset(ndev);
	if (ret)
		return ret;

	xge_port_init(ndev);
	pdata->nbufs = NUM_BUFS;

	return 0;
}