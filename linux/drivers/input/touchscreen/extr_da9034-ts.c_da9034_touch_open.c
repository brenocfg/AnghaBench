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
struct da9034_touch {int /*<<< orphan*/  state; int /*<<< orphan*/  da9034_dev; int /*<<< orphan*/  notifier; } ;

/* Variables and functions */
 int DA9034_EVENT_PEN_DOWN ; 
 int DA9034_EVENT_TSI_READY ; 
 int /*<<< orphan*/  DA9034_LDO_ADC_EN ; 
 int /*<<< orphan*/  DA9034_MANUAL_CTRL ; 
 int /*<<< orphan*/  DA9034_TSI_CTRL1 ; 
 int /*<<< orphan*/  DA9034_TSI_CTRL2 ; 
 int EBUSY ; 
 int /*<<< orphan*/  STATE_IDLE ; 
 int da903x_register_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int da903x_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int da903x_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  detect_pen_down (struct da9034_touch*,int) ; 
 struct da9034_touch* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static int da9034_touch_open(struct input_dev *dev)
{
	struct da9034_touch *touch = input_get_drvdata(dev);
	int ret;

	ret = da903x_register_notifier(touch->da9034_dev, &touch->notifier,
			DA9034_EVENT_PEN_DOWN | DA9034_EVENT_TSI_READY);
	if (ret)
		return -EBUSY;

	/* Enable ADC LDO */
	ret = da903x_set_bits(touch->da9034_dev,
			DA9034_MANUAL_CTRL, DA9034_LDO_ADC_EN);
	if (ret)
		return ret;

	/* TSI_DELAY: 3 slots, TSI_SKIP: 3 slots */
	ret = da903x_write(touch->da9034_dev, DA9034_TSI_CTRL1, 0x1b);
	if (ret)
		return ret;

	ret = da903x_write(touch->da9034_dev, DA9034_TSI_CTRL2, 0x00);
	if (ret)
		return ret;

	touch->state = STATE_IDLE;
	detect_pen_down(touch, 1);

	return 0;
}