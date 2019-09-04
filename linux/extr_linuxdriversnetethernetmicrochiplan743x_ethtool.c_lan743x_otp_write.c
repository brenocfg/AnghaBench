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
typedef  int u8 ;
typedef  int u32 ;
struct lan743x_adapter {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int EIO ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  OTP_ADDR1 ; 
 int OTP_ADDR1_15_11_MASK_ ; 
 int /*<<< orphan*/  OTP_ADDR2 ; 
 int OTP_ADDR2_10_3_MASK_ ; 
 int /*<<< orphan*/  OTP_CMD_GO ; 
 int OTP_CMD_GO_GO_ ; 
 int /*<<< orphan*/  OTP_PRGM_DATA ; 
 int /*<<< orphan*/  OTP_PRGM_MODE ; 
 int OTP_PRGM_MODE_BYTE_ ; 
 int /*<<< orphan*/  OTP_PWR_DN ; 
 int OTP_PWR_DN_PWRDN_N_ ; 
 int /*<<< orphan*/  OTP_STATUS ; 
 int OTP_STATUS_BUSY_ ; 
 int /*<<< orphan*/  OTP_TST_CMD ; 
 int OTP_TST_CMD_PRGVRFY_ ; 
 int /*<<< orphan*/  drv ; 
 unsigned long jiffies ; 
 int lan743x_csr_read (struct lan743x_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_warn (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int lan743x_otp_write(struct lan743x_adapter *adapter, u32 offset,
			     u32 length, u8 *data)
{
	unsigned long timeout;
	u32 buf;
	int i;

	buf = lan743x_csr_read(adapter, OTP_PWR_DN);

	if (buf & OTP_PWR_DN_PWRDN_N_) {
		/* clear it and wait to be cleared */
		lan743x_csr_write(adapter, OTP_PWR_DN, 0);

		timeout = jiffies + HZ;
		do {
			udelay(1);
			buf = lan743x_csr_read(adapter, OTP_PWR_DN);
			if (time_after(jiffies, timeout)) {
				netif_warn(adapter, drv, adapter->netdev,
					   "timeout on OTP_PWR_DN completion\n");
				return -EIO;
			}
		} while (buf & OTP_PWR_DN_PWRDN_N_);
	}

	/* set to BYTE program mode */
	lan743x_csr_write(adapter, OTP_PRGM_MODE, OTP_PRGM_MODE_BYTE_);

	for (i = 0; i < length; i++) {
		lan743x_csr_write(adapter, OTP_ADDR1,
				  ((offset + i) >> 8) &
				  OTP_ADDR1_15_11_MASK_);
		lan743x_csr_write(adapter, OTP_ADDR2,
				  ((offset + i) &
				  OTP_ADDR2_10_3_MASK_));
		lan743x_csr_write(adapter, OTP_PRGM_DATA, data[i]);
		lan743x_csr_write(adapter, OTP_TST_CMD, OTP_TST_CMD_PRGVRFY_);
		lan743x_csr_write(adapter, OTP_CMD_GO, OTP_CMD_GO_GO_);

		timeout = jiffies + HZ;
		do {
			udelay(1);
			buf = lan743x_csr_read(adapter, OTP_STATUS);
			if (time_after(jiffies, timeout)) {
				netif_warn(adapter, drv, adapter->netdev,
					   "Timeout on OTP_STATUS completion\n");
				return -EIO;
			}
		} while (buf & OTP_STATUS_BUSY_);
	}

	return 0;
}