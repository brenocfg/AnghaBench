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
typedef  int u32 ;
struct lan743x_adapter {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTP_CMD_CTL ; 
 int /*<<< orphan*/  drv ; 
 int lan743x_csr_read (struct lan743x_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void lan743x_ptp_wait_till_cmd_done(struct lan743x_adapter *adapter,
					   u32 bit_mask)
{
	int timeout = 1000;
	u32 data = 0;

	while (timeout &&
	       (data = (lan743x_csr_read(adapter, PTP_CMD_CTL) &
	       bit_mask))) {
		usleep_range(1000, 20000);
		timeout--;
	}
	if (data) {
		netif_err(adapter, drv, adapter->netdev,
			  "timeout waiting for cmd to be done, cmd = 0x%08X\n",
			  bit_mask);
	}
}