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
struct stmpe_touch {int /*<<< orphan*/  work; int /*<<< orphan*/  stmpe; int /*<<< orphan*/  idev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  STMPE_REG_TSC_CTRL ; 
 int /*<<< orphan*/  STMPE_REG_TSC_DATA_XYZ ; 
 int /*<<< orphan*/  STMPE_TSC_CTRL_TSC_EN ; 
 int /*<<< orphan*/  __stmpe_reset_fifo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmpe_block_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  stmpe_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t stmpe_ts_handler(int irq, void *data)
{
	u8 data_set[4];
	int x, y, z;
	struct stmpe_touch *ts = data;

	/*
	 * Cancel scheduled polling for release if we have new value
	 * available. Wait if the polling is already running.
	 */
	cancel_delayed_work_sync(&ts->work);

	/*
	 * The FIFO sometimes just crashes and stops generating interrupts. This
	 * appears to be a silicon bug. We still have to clearify this with
	 * the manufacture. As a workaround we disable the TSC while we are
	 * collecting data and flush the FIFO after reading
	 */
	stmpe_set_bits(ts->stmpe, STMPE_REG_TSC_CTRL,
				STMPE_TSC_CTRL_TSC_EN, 0);

	stmpe_block_read(ts->stmpe, STMPE_REG_TSC_DATA_XYZ, 4, data_set);

	x = (data_set[0] << 4) | (data_set[1] >> 4);
	y = ((data_set[1] & 0xf) << 8) | data_set[2];
	z = data_set[3];

	input_report_abs(ts->idev, ABS_X, x);
	input_report_abs(ts->idev, ABS_Y, y);
	input_report_abs(ts->idev, ABS_PRESSURE, z);
	input_report_key(ts->idev, BTN_TOUCH, 1);
	input_sync(ts->idev);

       /* flush the FIFO after we have read out our values. */
	__stmpe_reset_fifo(ts->stmpe);

	/* reenable the tsc */
	stmpe_set_bits(ts->stmpe, STMPE_REG_TSC_CTRL,
			STMPE_TSC_CTRL_TSC_EN, STMPE_TSC_CTRL_TSC_EN);

	/* start polling for touch_det to detect release */
	schedule_delayed_work(&ts->work, msecs_to_jiffies(50));

	return IRQ_HANDLED;
}