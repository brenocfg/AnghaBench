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
struct net_device {int dummy; } ;
struct macb {TYPE_1__* pdev; scalar_t__ ptp_clock; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_PTP_TIMER_NAME ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gem_ptp_clear_timer (struct macb*) ; 
 struct macb* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ptp_clock_unregister (scalar_t__) ; 

void gem_ptp_remove(struct net_device *ndev)
{
	struct macb *bp = netdev_priv(ndev);

	if (bp->ptp_clock)
		ptp_clock_unregister(bp->ptp_clock);

	gem_ptp_clear_timer(bp);

	dev_info(&bp->pdev->dev, "%s ptp clock unregistered.\n",
		 GEM_PTP_TIMER_NAME);
}