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
struct omap4_keypad {int no_autorepeat; int /*<<< orphan*/  cols; int /*<<< orphan*/  rows; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int matrix_keypad_parse_properties (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap4_keypad_parse_dt(struct device *dev,
				 struct omap4_keypad *keypad_data)
{
	struct device_node *np = dev->of_node;
	int err;

	err = matrix_keypad_parse_properties(dev, &keypad_data->rows,
					     &keypad_data->cols);
	if (err)
		return err;

	if (of_get_property(np, "linux,input-no-autorepeat", NULL))
		keypad_data->no_autorepeat = true;

	return 0;
}