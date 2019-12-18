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
struct xlgmac_desc_ops {int /*<<< orphan*/  (* free_channels_and_rings ) (struct xlgmac_pdata*) ;} ;
struct xlgmac_pdata {struct xlgmac_desc_ops desc_ops; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct xlgmac_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  xlgmac_stop (struct xlgmac_pdata*) ; 

__attribute__((used)) static int xlgmac_close(struct net_device *netdev)
{
	struct xlgmac_pdata *pdata = netdev_priv(netdev);
	struct xlgmac_desc_ops *desc_ops;

	desc_ops = &pdata->desc_ops;

	/* Stop the device */
	xlgmac_stop(pdata);

	/* Free the channels and rings */
	desc_ops->free_channels_and_rings(pdata);

	return 0;
}