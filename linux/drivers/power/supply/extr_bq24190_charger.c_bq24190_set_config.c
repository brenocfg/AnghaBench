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
struct bq24190_dev_info {int watchdog; int sys_min; int iprechg; int iterm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ24190_REG_CTTC ; 
 int BQ24190_REG_CTTC_WATCHDOG_MASK ; 
 int BQ24190_REG_CTTC_WATCHDOG_SHIFT ; 
 int /*<<< orphan*/  BQ24190_REG_PCTCC ; 
 int /*<<< orphan*/  BQ24190_REG_PCTCC_IPRECHG_MASK ; 
 int /*<<< orphan*/  BQ24190_REG_PCTCC_IPRECHG_SHIFT ; 
 int /*<<< orphan*/  BQ24190_REG_PCTCC_ITERM_MASK ; 
 int /*<<< orphan*/  BQ24190_REG_PCTCC_ITERM_SHIFT ; 
 int /*<<< orphan*/  BQ24190_REG_POC ; 
 int /*<<< orphan*/  BQ24190_REG_POC_SYS_MIN_MASK ; 
 int /*<<< orphan*/  BQ24190_REG_POC_SYS_MIN_SHIFT ; 
 int bq24190_read (struct bq24190_dev_info*,int /*<<< orphan*/ ,int*) ; 
 int bq24190_write (struct bq24190_dev_info*,int /*<<< orphan*/ ,int) ; 
 int bq24190_write_mask (struct bq24190_dev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bq24190_set_config(struct bq24190_dev_info *bdi)
{
	int ret;
	u8 v;

	ret = bq24190_read(bdi, BQ24190_REG_CTTC, &v);
	if (ret < 0)
		return ret;

	bdi->watchdog = ((v & BQ24190_REG_CTTC_WATCHDOG_MASK) >>
					BQ24190_REG_CTTC_WATCHDOG_SHIFT);

	/*
	 * According to the "Host Mode and default Mode" section of the
	 * manual, a write to any register causes the bq24190 to switch
	 * from default mode to host mode.  It will switch back to default
	 * mode after a WDT timeout unless the WDT is turned off as well.
	 * So, by simply turning off the WDT, we accomplish both with the
	 * same write.
	 */
	v &= ~BQ24190_REG_CTTC_WATCHDOG_MASK;

	ret = bq24190_write(bdi, BQ24190_REG_CTTC, v);
	if (ret < 0)
		return ret;

	if (bdi->sys_min) {
		v = bdi->sys_min / 100 - 30; // manual section 9.5.1.2, table 9
		ret = bq24190_write_mask(bdi, BQ24190_REG_POC,
					 BQ24190_REG_POC_SYS_MIN_MASK,
					 BQ24190_REG_POC_SYS_MIN_SHIFT,
					 v);
		if (ret < 0)
			return ret;
	}

	if (bdi->iprechg) {
		v = bdi->iprechg / 128 - 1; // manual section 9.5.1.4, table 11
		ret = bq24190_write_mask(bdi, BQ24190_REG_PCTCC,
					 BQ24190_REG_PCTCC_IPRECHG_MASK,
					 BQ24190_REG_PCTCC_IPRECHG_SHIFT,
					 v);
		if (ret < 0)
			return ret;
	}

	if (bdi->iterm) {
		v = bdi->iterm / 128 - 1; // manual section 9.5.1.4, table 11
		ret = bq24190_write_mask(bdi, BQ24190_REG_PCTCC,
					 BQ24190_REG_PCTCC_ITERM_MASK,
					 BQ24190_REG_PCTCC_ITERM_SHIFT,
					 v);
		if (ret < 0)
			return ret;
	}

	return 0;
}