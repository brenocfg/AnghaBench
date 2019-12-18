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
struct lan743x_ptp {int /*<<< orphan*/  command_lock; } ;
struct lan743x_adapter {int /*<<< orphan*/  netdev; struct lan743x_ptp ptp; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTP_CMD_CTL ; 
 int /*<<< orphan*/  PTP_CMD_CTL_PTP_DISABLE_ ; 
 int /*<<< orphan*/  PTP_CMD_CTL_PTP_ENABLE_ ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan743x_ptp_is_enabled (struct lan743x_adapter*) ; 
 int /*<<< orphan*/  lan743x_ptp_wait_till_cmd_done (struct lan743x_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_warn (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void lan743x_ptp_disable(struct lan743x_adapter *adapter)
{
	struct lan743x_ptp *ptp = &adapter->ptp;

	mutex_lock(&ptp->command_lock);
	if (!lan743x_ptp_is_enabled(adapter)) {
		netif_warn(adapter, drv, adapter->netdev,
			   "PTP already disabled\n");
		goto done;
	}
	lan743x_csr_write(adapter, PTP_CMD_CTL, PTP_CMD_CTL_PTP_DISABLE_);
	lan743x_ptp_wait_till_cmd_done(adapter, PTP_CMD_CTL_PTP_ENABLE_);
done:
	mutex_unlock(&ptp->command_lock);
}