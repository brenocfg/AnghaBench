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
struct ixgbe_adapter {int /*<<< orphan*/  state; int /*<<< orphan*/  ptp_tx_work; int /*<<< orphan*/  tmreg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __IXGBE_PTP_RUNNING ; 
 scalar_t__ ixgbe_ptp_create_clock (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_ptp_reset (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_ptp_tx_hwtstamp_work ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void ixgbe_ptp_init(struct ixgbe_adapter *adapter)
{
	/* initialize the spin lock first since we can't control when a user
	 * will call the entry functions once we have initialized the clock
	 * device
	 */
	spin_lock_init(&adapter->tmreg_lock);

	/* obtain a PTP device, or re-use an existing device */
	if (ixgbe_ptp_create_clock(adapter))
		return;

	/* we have a clock so we can initialize work now */
	INIT_WORK(&adapter->ptp_tx_work, ixgbe_ptp_tx_hwtstamp_work);

	/* reset the PTP related hardware bits */
	ixgbe_ptp_reset(adapter);

	/* enter the IXGBE_PTP_RUNNING state */
	set_bit(__IXGBE_PTP_RUNNING, &adapter->state);

	return;
}