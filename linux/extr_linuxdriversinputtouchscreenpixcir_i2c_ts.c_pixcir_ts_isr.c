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
struct pixcir_report_data {scalar_t__ num_touches; } ;
struct pixcir_i2c_ts_data {int /*<<< orphan*/  input; int /*<<< orphan*/  gpio_attb; scalar_t__ running; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ gpiod_get_value_cansleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_mt_sync_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pixcir_ts_parse (struct pixcir_i2c_ts_data*,struct pixcir_report_data*) ; 
 int /*<<< orphan*/  pixcir_ts_report (struct pixcir_i2c_ts_data*,struct pixcir_report_data*) ; 

__attribute__((used)) static irqreturn_t pixcir_ts_isr(int irq, void *dev_id)
{
	struct pixcir_i2c_ts_data *tsdata = dev_id;
	struct pixcir_report_data report;

	while (tsdata->running) {
		/* parse packet */
		pixcir_ts_parse(tsdata, &report);

		/* report it */
		pixcir_ts_report(tsdata, &report);

		if (gpiod_get_value_cansleep(tsdata->gpio_attb)) {
			if (report.num_touches) {
				/*
				 * Last report with no finger up?
				 * Do it now then.
				 */
				input_mt_sync_frame(tsdata->input);
				input_sync(tsdata->input);
			}
			break;
		}

		msleep(20);
	}

	return IRQ_HANDLED;
}