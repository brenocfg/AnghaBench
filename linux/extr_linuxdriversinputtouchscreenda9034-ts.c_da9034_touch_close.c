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
struct input_dev {int dummy; } ;
struct da9034_touch {int /*<<< orphan*/  da9034_dev; int /*<<< orphan*/  state; int /*<<< orphan*/  tsi_work; int /*<<< orphan*/  notifier; } ;

/* Variables and functions */
 int DA9034_EVENT_PEN_DOWN ; 
 int DA9034_EVENT_TSI_READY ; 
 int /*<<< orphan*/  DA9034_LDO_ADC_EN ; 
 int /*<<< orphan*/  DA9034_MANUAL_CTRL ; 
 int /*<<< orphan*/  STATE_IDLE ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  da903x_clr_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da903x_unregister_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  detect_pen_down (struct da9034_touch*,int /*<<< orphan*/ ) ; 
 struct da9034_touch* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  stop_tsi (struct da9034_touch*) ; 

__attribute__((used)) static void da9034_touch_close(struct input_dev *dev)
{
	struct da9034_touch *touch = input_get_drvdata(dev);

	da903x_unregister_notifier(touch->da9034_dev, &touch->notifier,
			DA9034_EVENT_PEN_DOWN | DA9034_EVENT_TSI_READY);

	cancel_delayed_work_sync(&touch->tsi_work);

	touch->state = STATE_IDLE;
	stop_tsi(touch);
	detect_pen_down(touch, 0);

	/* Disable ADC LDO */
	da903x_clr_bits(touch->da9034_dev,
			DA9034_MANUAL_CTRL, DA9034_LDO_ADC_EN);
}