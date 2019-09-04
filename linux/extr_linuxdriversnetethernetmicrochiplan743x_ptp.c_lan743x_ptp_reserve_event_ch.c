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
struct lan743x_ptp {int /*<<< orphan*/  command_lock; int /*<<< orphan*/  used_event_ch; } ;
struct lan743x_adapter {struct lan743x_ptp ptp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int ENODEV ; 
 int LAN743X_PTP_NUMBER_OF_EVENT_CHANNELS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lan743x_ptp_reserve_event_ch(struct lan743x_adapter *adapter)
{
	struct lan743x_ptp *ptp = &adapter->ptp;
	int result = -ENODEV;
	int index = 0;

	mutex_lock(&ptp->command_lock);
	for (index = 0; index < LAN743X_PTP_NUMBER_OF_EVENT_CHANNELS; index++) {
		if (!(test_bit(index, &ptp->used_event_ch))) {
			ptp->used_event_ch |= BIT(index);
			result = index;
			break;
		}
	}
	mutex_unlock(&ptp->command_lock);
	return result;
}