#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct input_dev {int dummy; } ;
struct gpio_keys_drvdata {struct gpio_button_data* data; TYPE_1__* pdata; struct input_dev* input; } ;
struct gpio_button_data {scalar_t__ gpiod; } ;
struct TYPE_2__ {int nbuttons; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_keys_gpio_report_event (struct gpio_button_data*) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void gpio_keys_report_state(struct gpio_keys_drvdata *ddata)
{
	struct input_dev *input = ddata->input;
	int i;

	for (i = 0; i < ddata->pdata->nbuttons; i++) {
		struct gpio_button_data *bdata = &ddata->data[i];
		if (bdata->gpiod)
			gpio_keys_gpio_report_event(bdata);
	}
	input_sync(input);
}