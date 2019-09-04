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
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  device_property_read_u32 (struct device*,char*,unsigned int*) ; 

int matrix_keypad_parse_properties(struct device *dev,
				   unsigned int *rows, unsigned int *cols)
{
	*rows = *cols = 0;

	device_property_read_u32(dev, "keypad,num-rows", rows);
	device_property_read_u32(dev, "keypad,num-columns", cols);

	if (!*rows || !*cols) {
		dev_err(dev, "number of keypad rows/columns not specified\n");
		return -EINVAL;
	}

	return 0;
}