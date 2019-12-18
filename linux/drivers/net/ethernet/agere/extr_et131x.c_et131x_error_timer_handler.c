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
struct timer_list {int dummy; } ;
struct phy_device {int /*<<< orphan*/  link; } ;
struct et131x_adapter {int boot_coma; int /*<<< orphan*/  error_timer; TYPE_1__* netdev; } ;
struct TYPE_2__ {struct phy_device* phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_ERROR_PERIOD ; 
 struct et131x_adapter* adapter ; 
 int /*<<< orphan*/  error_timer ; 
 int /*<<< orphan*/  et1310_disable_phy_coma (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et1310_enable_phy_coma (struct et131x_adapter*) ; 
 scalar_t__ et1310_in_phy_coma (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et1310_update_macstat_host_counters (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_enable_interrupts (struct et131x_adapter*) ; 
 struct et131x_adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void et131x_error_timer_handler(struct timer_list *t)
{
	struct et131x_adapter *adapter = from_timer(adapter, t, error_timer);
	struct phy_device *phydev = adapter->netdev->phydev;

	if (et1310_in_phy_coma(adapter)) {
		/* Bring the device immediately out of coma, to
		 * prevent it from sleeping indefinitely, this
		 * mechanism could be improved!
		 */
		et1310_disable_phy_coma(adapter);
		adapter->boot_coma = 20;
	} else {
		et1310_update_macstat_host_counters(adapter);
	}

	if (!phydev->link && adapter->boot_coma < 11)
		adapter->boot_coma++;

	if (adapter->boot_coma == 10) {
		if (!phydev->link) {
			if (!et1310_in_phy_coma(adapter)) {
				/* NOTE - This was originally a 'sync with
				 *  interrupt'. How to do that under Linux?
				 */
				et131x_enable_interrupts(adapter);
				et1310_enable_phy_coma(adapter);
			}
		}
	}

	/* This is a periodic timer, so reschedule */
	mod_timer(&adapter->error_timer, jiffies +
		  msecs_to_jiffies(TX_ERROR_PERIOD));
}