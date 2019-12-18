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
struct ixgbe_adapter {TYPE_1__* netdev; int /*<<< orphan*/ * ptp_clock; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  e_dev_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_ptp_suspend (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ptp_clock_unregister (int /*<<< orphan*/ *) ; 

void ixgbe_ptp_stop(struct ixgbe_adapter *adapter)
{
	/* first, suspend PTP activity */
	ixgbe_ptp_suspend(adapter);

	/* disable the PTP clock device */
	if (adapter->ptp_clock) {
		ptp_clock_unregister(adapter->ptp_clock);
		adapter->ptp_clock = NULL;
		e_dev_info("removed PHC on %s\n",
			   adapter->netdev->name);
	}
}