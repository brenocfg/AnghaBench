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
struct trf7970a {scalar_t__ state; int aborting; int /*<<< orphan*/  dev; int /*<<< orphan*/  chip_status_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRF7970A_CHIP_STATUS_CTRL ; 
 int /*<<< orphan*/  TRF7970A_CHIP_STATUS_RF_ON ; 
 scalar_t__ TRF7970A_ST_PWR_OFF ; 
 scalar_t__ TRF7970A_ST_RF_OFF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trf7970a_write (struct trf7970a*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void trf7970a_switch_rf_off(struct trf7970a *trf)
{
	if ((trf->state == TRF7970A_ST_PWR_OFF) ||
	    (trf->state == TRF7970A_ST_RF_OFF))
		return;

	dev_dbg(trf->dev, "Switching rf off\n");

	trf->chip_status_ctrl &= ~TRF7970A_CHIP_STATUS_RF_ON;

	trf7970a_write(trf, TRF7970A_CHIP_STATUS_CTRL, trf->chip_status_ctrl);

	trf->aborting = false;
	trf->state = TRF7970A_ST_RF_OFF;

	pm_runtime_mark_last_busy(trf->dev);
	pm_runtime_put_autosuspend(trf->dev);
}