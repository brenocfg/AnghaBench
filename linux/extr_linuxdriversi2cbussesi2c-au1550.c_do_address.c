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
struct i2c_au1550_data {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PSC_SMBEVNT ; 
 unsigned int PSC_SMBEVNT_ALLCLR ; 
 int /*<<< orphan*/  PSC_SMBPCR ; 
 unsigned int PSC_SMBPCR_DC ; 
 unsigned int PSC_SMBPCR_MS ; 
 int /*<<< orphan*/  PSC_SMBSTAT ; 
 unsigned long PSC_SMBSTAT_RE ; 
 unsigned long PSC_SMBSTAT_TE ; 
 int /*<<< orphan*/  PSC_SMBTXRX ; 
 unsigned int PSC_SMBTXRX_STP ; 
 unsigned int RD (struct i2c_au1550_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR (struct i2c_au1550_data*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ wait_ack (struct i2c_au1550_data*) ; 
 int wait_master_done (struct i2c_au1550_data*) ; 

__attribute__((used)) static int
do_address(struct i2c_au1550_data *adap, unsigned int addr, int rd, int q)
{
	unsigned long stat;

	/* Reset the FIFOs, clear events. */
	stat = RD(adap, PSC_SMBSTAT);
	WR(adap, PSC_SMBEVNT, PSC_SMBEVNT_ALLCLR);

	if (!(stat & PSC_SMBSTAT_TE) || !(stat & PSC_SMBSTAT_RE)) {
		WR(adap, PSC_SMBPCR, PSC_SMBPCR_DC);
		while ((RD(adap, PSC_SMBPCR) & PSC_SMBPCR_DC) != 0)
			cpu_relax();
		udelay(50);
	}

	/* Write out the i2c chip address and specify operation */
	addr <<= 1;
	if (rd)
		addr |= 1;

	/* zero-byte xfers stop immediately */
	if (q)
		addr |= PSC_SMBTXRX_STP;

	/* Put byte into fifo, start up master. */
	WR(adap, PSC_SMBTXRX, addr);
	WR(adap, PSC_SMBPCR, PSC_SMBPCR_MS);
	if (wait_ack(adap))
		return -EIO;
	return (q) ? wait_master_done(adap) : 0;
}