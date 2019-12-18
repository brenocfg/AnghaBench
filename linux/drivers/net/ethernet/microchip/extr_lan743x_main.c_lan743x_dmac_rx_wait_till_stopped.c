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
struct lan743x_adapter {int dummy; } ;

/* Variables and functions */
 int DMAC_CHANNEL_STATE_STOP_PENDING ; 
 int ENODEV ; 
 int lan743x_dmac_rx_get_state (struct lan743x_adapter*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int lan743x_dmac_rx_wait_till_stopped(struct lan743x_adapter *adapter,
					     int rx_channel)
{
	int timeout = 100;
	int result = 0;

	while (timeout &&
	       ((result = lan743x_dmac_rx_get_state(adapter, rx_channel)) ==
	       DMAC_CHANNEL_STATE_STOP_PENDING)) {
		usleep_range(1000, 20000);
		timeout--;
	}
	if (result == DMAC_CHANNEL_STATE_STOP_PENDING)
		result = -ENODEV;
	return result;
}