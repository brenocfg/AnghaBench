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
struct trf7970a {int state; int io_ctrl; int modulator_sys_clk_ctrl; int iso_ctrl; int /*<<< orphan*/  dev; scalar_t__ special_fcn_reg1; int /*<<< orphan*/  chip_status_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRF7970A_ADJUTABLE_FIFO_IRQ_LEVELS ; 
 int TRF7970A_ADJUTABLE_FIFO_IRQ_LEVELS_WLH_96 ; 
 int TRF7970A_ADJUTABLE_FIFO_IRQ_LEVELS_WLL_32 ; 
 int /*<<< orphan*/  TRF7970A_CHIP_STATUS_RF_ON ; 
 int /*<<< orphan*/  TRF7970A_CMD_IDLE ; 
 int /*<<< orphan*/  TRF7970A_CMD_SOFT_INIT ; 
 int /*<<< orphan*/  TRF7970A_MODULATOR_SYS_CLK_CTRL ; 
 int /*<<< orphan*/  TRF7970A_NFC_TARGET_LEVEL ; 
 int /*<<< orphan*/  TRF7970A_REG_IO_CTRL ; 
 int TRF7970A_REG_IO_CTRL_VRS (int) ; 
 int /*<<< orphan*/  TRF7970A_SPECIAL_FCN_REG1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int trf7970a_cmd (struct trf7970a*,int /*<<< orphan*/ ) ; 
 int trf7970a_write (struct trf7970a*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int trf7970a_init(struct trf7970a *trf)
{
	int ret;

	dev_dbg(trf->dev, "Initializing device - state: %d\n", trf->state);

	ret = trf7970a_cmd(trf, TRF7970A_CMD_SOFT_INIT);
	if (ret)
		goto err_out;

	ret = trf7970a_cmd(trf, TRF7970A_CMD_IDLE);
	if (ret)
		goto err_out;

	ret = trf7970a_write(trf, TRF7970A_REG_IO_CTRL,
			     trf->io_ctrl | TRF7970A_REG_IO_CTRL_VRS(0x1));
	if (ret)
		goto err_out;

	ret = trf7970a_write(trf, TRF7970A_NFC_TARGET_LEVEL, 0);
	if (ret)
		goto err_out;

	usleep_range(1000, 2000);

	trf->chip_status_ctrl &= ~TRF7970A_CHIP_STATUS_RF_ON;

	ret = trf7970a_write(trf, TRF7970A_MODULATOR_SYS_CLK_CTRL,
			     trf->modulator_sys_clk_ctrl);
	if (ret)
		goto err_out;

	ret = trf7970a_write(trf, TRF7970A_ADJUTABLE_FIFO_IRQ_LEVELS,
			     TRF7970A_ADJUTABLE_FIFO_IRQ_LEVELS_WLH_96 |
			     TRF7970A_ADJUTABLE_FIFO_IRQ_LEVELS_WLL_32);
	if (ret)
		goto err_out;

	ret = trf7970a_write(trf, TRF7970A_SPECIAL_FCN_REG1, 0);
	if (ret)
		goto err_out;

	trf->special_fcn_reg1 = 0;

	trf->iso_ctrl = 0xff;
	return 0;

err_out:
	dev_dbg(trf->dev, "Couldn't init device: %d\n", ret);
	return ret;
}