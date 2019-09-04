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
struct platform_device {int dummy; } ;
struct jornada_ts {int /*<<< orphan*/  y_data; int /*<<< orphan*/  x_data; int /*<<< orphan*/  gpio; struct input_dev* dev; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  GETTOUCHSAMPLES ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ TXDUMMY ; 
 scalar_t__ gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int jornada720_ts_average (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jornada720_ts_collect_data (struct jornada_ts*) ; 
 int /*<<< orphan*/  jornada_ssp_end () ; 
 scalar_t__ jornada_ssp_inout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jornada_ssp_start () ; 
 struct jornada_ts* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static irqreturn_t jornada720_ts_interrupt(int irq, void *dev_id)
{
	struct platform_device *pdev = dev_id;
	struct jornada_ts *jornada_ts = platform_get_drvdata(pdev);
	struct input_dev *input = jornada_ts->dev;
	int x, y;

	/* If gpio is high then report pen up */
	if (gpiod_get_value(jornada_ts->gpio)) {
		input_report_key(input, BTN_TOUCH, 0);
		input_sync(input);
	} else {
		jornada_ssp_start();

		/* proper reply to request is always TXDUMMY */
		if (jornada_ssp_inout(GETTOUCHSAMPLES) == TXDUMMY) {
			jornada720_ts_collect_data(jornada_ts);

			x = jornada720_ts_average(jornada_ts->x_data);
			y = jornada720_ts_average(jornada_ts->y_data);

			input_report_key(input, BTN_TOUCH, 1);
			input_report_abs(input, ABS_X, x);
			input_report_abs(input, ABS_Y, y);
			input_sync(input);
		}

		jornada_ssp_end();
	}

	return IRQ_HANDLED;
}