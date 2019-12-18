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
 int EIO ; 
 int /*<<< orphan*/  PSC_SMBSTAT ; 
 unsigned char PSC_SMBSTAT_RE ; 
 int /*<<< orphan*/  PSC_SMBTXRX ; 
 unsigned char RD (struct i2c_au1550_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ wait_xfer_done (struct i2c_au1550_data*) ; 

__attribute__((used)) static int wait_for_rx_byte(struct i2c_au1550_data *adap, unsigned char *out)
{
	int j;

	if (wait_xfer_done(adap))
		return -EIO;

	j =  adap->xfer_timeout * 100;
	do {
		j--;
		if (j <= 0)
			return -EIO;

		if ((RD(adap, PSC_SMBSTAT) & PSC_SMBSTAT_RE) == 0)
			j = 0;
		else
			udelay(1);
	} while (j > 0);

	*out = RD(adap, PSC_SMBTXRX);

	return 0;
}