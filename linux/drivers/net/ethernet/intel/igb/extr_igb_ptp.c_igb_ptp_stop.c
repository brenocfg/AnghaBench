#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct igb_adapter {int /*<<< orphan*/  ptp_flags; TYPE_2__* netdev; TYPE_1__* pdev; scalar_t__ ptp_clock; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGB_PTP_ENABLED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igb_ptp_suspend (struct igb_adapter*) ; 
 int /*<<< orphan*/  ptp_clock_unregister (scalar_t__) ; 

void igb_ptp_stop(struct igb_adapter *adapter)
{
	igb_ptp_suspend(adapter);

	if (adapter->ptp_clock) {
		ptp_clock_unregister(adapter->ptp_clock);
		dev_info(&adapter->pdev->dev, "removed PHC on %s\n",
			 adapter->netdev->name);
		adapter->ptp_flags &= ~IGB_PTP_ENABLED;
	}
}