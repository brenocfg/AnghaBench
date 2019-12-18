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
struct smsc911x_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_DATA_FIFO ; 
 int /*<<< orphan*/  RX_DP_CTRL ; 
 unsigned int RX_DP_CTRL_RX_FFWD_ ; 
 int /*<<< orphan*/  SMSC_WARN (struct smsc911x_data*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  hw ; 
 scalar_t__ likely (int) ; 
 unsigned int smsc911x_reg_read (struct smsc911x_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc911x_reg_write (struct smsc911x_data*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
smsc911x_rx_fastforward(struct smsc911x_data *pdata, unsigned int pktwords)
{
	if (likely(pktwords >= 4)) {
		unsigned int timeout = 500;
		unsigned int val;
		smsc911x_reg_write(pdata, RX_DP_CTRL, RX_DP_CTRL_RX_FFWD_);
		do {
			udelay(1);
			val = smsc911x_reg_read(pdata, RX_DP_CTRL);
		} while ((val & RX_DP_CTRL_RX_FFWD_) && --timeout);

		if (unlikely(timeout == 0))
			SMSC_WARN(pdata, hw, "Timed out waiting for "
				  "RX FFWD to finish, RX_DP_CTRL: 0x%08X", val);
	} else {
		unsigned int temp;
		while (pktwords--)
			temp = smsc911x_reg_read(pdata, RX_DATA_FIFO);
	}
}