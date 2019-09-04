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
typedef  unsigned long long u64 ;
struct qib_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_7220_SERDES ; 
 int /*<<< orphan*/  IB_CTRL2 (int) ; 
 int /*<<< orphan*/  IB_MPREG6 ; 
 int /*<<< orphan*/  IB_PGUDP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kr_ibcstatus ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*,...) ; 
 unsigned long long qib_read_kreg64 (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int qib_resync_ibepb (struct qib_devdata*) ; 
 int qib_sd7220_reg_mod (struct qib_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void qib_sd_trimdone_monitor(struct qib_devdata *dd,
	const char *where)
{
	int ret, chn, baduns;
	u64 val;

	if (!where)
		where = "?";

	/* give time for reset to settle out in EPB */
	udelay(2);

	ret = qib_resync_ibepb(dd);
	if (ret < 0)
		qib_dev_err(dd, "not able to re-sync IB EPB (%s)\n", where);

	/* Do "sacrificial read" to get EPB in sane state after reset */
	ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES, IB_CTRL2(0), 0, 0);
	if (ret < 0)
		qib_dev_err(dd, "Failed TRIMDONE 1st read, (%s)\n", where);

	/* Check/show "summary" Trim-done bit in IBCStatus */
	val = qib_read_kreg64(dd, kr_ibcstatus);
	if (!(val & (1ULL << 11)))
		qib_dev_err(dd, "IBCS TRIMDONE clear (%s)\n", where);
	/*
	 * Do "dummy read/mod/wr" to get EPB in sane state after reset
	 * The default value for MPREG6 is 0.
	 */
	udelay(2);

	ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES, IB_MPREG6, 0x80, 0x80);
	if (ret < 0)
		qib_dev_err(dd, "Failed Dummy RMW, (%s)\n", where);
	udelay(10);

	baduns = 0;

	for (chn = 3; chn >= 0; --chn) {
		/* Read CTRL reg for each channel to check TRIMDONE */
		ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES,
			IB_CTRL2(chn), 0, 0);
		if (ret < 0)
			qib_dev_err(dd,
				"Failed checking TRIMDONE, chn %d (%s)\n",
				chn, where);

		if (!(ret & 0x10)) {
			int probe;

			baduns |= (1 << chn);
			qib_dev_err(dd,
				"TRIMDONE cleared on chn %d (%02X). (%s)\n",
				chn, ret, where);
			probe = qib_sd7220_reg_mod(dd, IB_7220_SERDES,
				IB_PGUDP(0), 0, 0);
			qib_dev_err(dd, "probe is %d (%02X)\n",
				probe, probe);
			probe = qib_sd7220_reg_mod(dd, IB_7220_SERDES,
				IB_CTRL2(chn), 0, 0);
			qib_dev_err(dd, "re-read: %d (%02X)\n",
				probe, probe);
			ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES,
				IB_CTRL2(chn), 0x10, 0x10);
			if (ret < 0)
				qib_dev_err(dd,
					"Err on TRIMDONE rewrite1\n");
		}
	}
	for (chn = 3; chn >= 0; --chn) {
		/* Read CTRL reg for each channel to check TRIMDONE */
		if (baduns & (1 << chn)) {
			qib_dev_err(dd,
				"Resetting TRIMDONE on chn %d (%s)\n",
				chn, where);
			ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES,
				IB_CTRL2(chn), 0x10, 0x10);
			if (ret < 0)
				qib_dev_err(dd,
					"Failed re-setting TRIMDONE, chn %d (%s)\n",
					chn, where);
		}
	}
}