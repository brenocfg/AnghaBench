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
struct i2c_au1550_data {int xfer_timeout; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  PSC_SMBSTAT ; 
 int PSC_SMBSTAT_TE ; 
 int RD (struct i2c_au1550_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int wait_xfer_done(struct i2c_au1550_data *adap)
{
	int i;

	/* Wait for Tx Buffer Empty */
	for (i = 0; i < adap->xfer_timeout; i++) {
		if (RD(adap, PSC_SMBSTAT) & PSC_SMBSTAT_TE)
			return 0;

		udelay(1);
	}

	return -ETIMEDOUT;
}