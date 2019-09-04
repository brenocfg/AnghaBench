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
struct gpio {int /*<<< orphan*/  gpio; int /*<<< orphan*/  label; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int gpio_request_array(const struct gpio *array, size_t num)
{
	int i, err;

	for (i = 0; i < num; i++, array++) {
		err = gpio_request_one(array->gpio, array->flags, array->label);
		if (err)
			goto err_free;
	}
	return 0;

err_free:
	while (i--)
		gpio_free((--array)->gpio);
	return err;
}