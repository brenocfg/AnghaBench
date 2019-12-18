#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;
struct xge_pdata {TYPE_1__ resources; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct xge_pdata*) ; 
 struct xge_pdata* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void xge_free_irq(struct net_device *ndev)
{
	struct xge_pdata *pdata = netdev_priv(ndev);

	free_irq(pdata->resources.irq, pdata);
}