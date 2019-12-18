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
struct input_dev {int /*<<< orphan*/  led; } ;
struct applespi_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  EV_LED 128 
 int /*<<< orphan*/  LED_CAPSL ; 
 int /*<<< orphan*/  applespi_set_capsl_led (struct applespi_data*,int) ; 
 struct applespi_data* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int applespi_event(struct input_dev *dev, unsigned int type,
			  unsigned int code, int value)
{
	struct applespi_data *applespi = input_get_drvdata(dev);

	switch (type) {
	case EV_LED:
		applespi_set_capsl_led(applespi, !!test_bit(LED_CAPSL, dev->led));
		return 0;
	}

	return -EINVAL;
}