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
 int /*<<< orphan*/  PSC_SMBEVNT ; 
 int PSC_SMBEVNT_MD ; 
 int RD (struct i2c_au1550_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int wait_master_done(struct i2c_au1550_data *adap)
{
	int i;

	/* Wait for Master Done. */
	for (i = 0; i < 2 * adap->xfer_timeout; i++) {
		if ((RD(adap, PSC_SMBEVNT) & PSC_SMBEVNT_MD) != 0)
			return 0;
		udelay(1);
	}

	return -ETIMEDOUT;
}