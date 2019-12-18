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
typedef  int /*<<< orphan*/  u8 ;
struct bu21029_ts_data {int /*<<< orphan*/  timer; int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  BU21029_AUTOSCAN ; 
 int BUF_LEN ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  PEN_UP_TIMEOUT_MS ; 
 int /*<<< orphan*/  bu21029_touch_report (struct bu21029_ts_data*,int /*<<< orphan*/ *) ; 
 int i2c_smbus_read_i2c_block_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t bu21029_touch_soft_irq(int irq, void *data)
{
	struct bu21029_ts_data *bu21029 = data;
	u8 buf[BUF_LEN];
	int error;

	/*
	 * Read touch data and deassert interrupt (will assert again after
	 * INTVL_TIME + tConv4 for continuous touch)
	 */
	error = i2c_smbus_read_i2c_block_data(bu21029->client, BU21029_AUTOSCAN,
					      sizeof(buf), buf);
	if (error < 0)
		goto out;

	bu21029_touch_report(bu21029, buf);

	/* reset timer for pen up detection */
	mod_timer(&bu21029->timer,
		  jiffies + msecs_to_jiffies(PEN_UP_TIMEOUT_MS));

out:
	return IRQ_HANDLED;
}