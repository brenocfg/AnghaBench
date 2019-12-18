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
 int EIO ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  OTP_STATUS ; 
 int OTP_STATUS_BUSY_ ; 
 int /*<<< orphan*/  drv ; 
 unsigned long jiffies ; 
 int lan743x_csr_read (struct lan743x_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_warn (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int lan743x_otp_wait_till_not_busy(struct lan743x_adapter *adapter)
{
	unsigned long timeout;
	u32 reg_val;

	timeout = jiffies + HZ;
	do {
		if (time_after(jiffies, timeout)) {
			netif_warn(adapter, drv, adapter->netdev,
				   "Timeout on OTP_STATUS completion\n");
			return -EIO;
		}
		udelay(1);
		reg_val = lan743x_csr_read(adapter, OTP_STATUS);
	} while (reg_val & OTP_STATUS_BUSY_);

	return 0;
}