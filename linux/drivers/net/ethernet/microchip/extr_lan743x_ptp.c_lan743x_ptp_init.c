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
struct lan743x_ptp {int perout_event_ch; int perout_gpio_bit; scalar_t__ used_event_ch; int /*<<< orphan*/  tx_ts_lock; int /*<<< orphan*/  command_lock; } ;
struct lan743x_adapter {struct lan743x_ptp ptp; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int lan743x_ptp_init(struct lan743x_adapter *adapter)
{
	struct lan743x_ptp *ptp = &adapter->ptp;

	mutex_init(&ptp->command_lock);
	spin_lock_init(&ptp->tx_ts_lock);
	ptp->used_event_ch = 0;
	ptp->perout_event_ch = -1;
	ptp->perout_gpio_bit = -1;
	return 0;
}