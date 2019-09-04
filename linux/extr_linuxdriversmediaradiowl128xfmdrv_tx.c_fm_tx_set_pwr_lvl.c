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
typedef  void* u8 ;
typedef  void* u16 ;
struct fmtx_data {void* pwr_lvl; } ;
struct fmdev {scalar_t__ curr_fmmode; int /*<<< orphan*/  flag; struct fmtx_data tx_data; } ;
typedef  int /*<<< orphan*/  payload ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  FM_CORE_READY ; 
 scalar_t__ FM_MODE_TX ; 
 void* FM_PWR_LVL_HIGH ; 
 int /*<<< orphan*/  POWER_LEV_SET ; 
 int /*<<< orphan*/  REG_WR ; 
 int fmc_send_cmd (struct fmdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmdbg (char*,long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int fm_tx_set_pwr_lvl(struct fmdev *fmdev, u8 new_pwr_lvl)
{
	u16 payload;
	struct fmtx_data *tx = &fmdev->tx_data;
	int ret;

	if (fmdev->curr_fmmode != FM_MODE_TX)
		return -EPERM;
	fmdbg("tx: pwr_level_to_set %ld\n", (long int)new_pwr_lvl);

	/* If the core isn't ready update global variable */
	if (!test_bit(FM_CORE_READY, &fmdev->flag)) {
		tx->pwr_lvl = new_pwr_lvl;
		return 0;
	}

	/* Set power level: Application will specify power level value in
	 * units of dB/uV, whereas range and step are specific to FM chip.
	 * For TI's WL chips, convert application specified power level value
	 * to chip specific value by subtracting 122 from it. Refer to TI FM
	 * data sheet for details.
	 * */

	payload = (FM_PWR_LVL_HIGH - new_pwr_lvl);
	ret = fmc_send_cmd(fmdev, POWER_LEV_SET, REG_WR, &payload,
			sizeof(payload), NULL, NULL);
	if (ret < 0)
		return ret;

	/* TODO: is the power level set? */
	tx->pwr_lvl = new_pwr_lvl;

	return 0;
}