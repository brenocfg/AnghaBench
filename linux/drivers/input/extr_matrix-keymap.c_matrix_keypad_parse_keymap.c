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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {struct device* parent; } ;
struct input_dev {TYPE_1__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char const*,int,...) ; 
 int device_property_count_u32 (struct device*,char const*) ; 
 int device_property_read_u32_array (struct device*,char const*,int /*<<< orphan*/ *,int) ; 
 unsigned int get_count_order (unsigned int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matrix_keypad_map_key (struct input_dev*,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int matrix_keypad_parse_keymap(const char *propname,
				      unsigned int rows, unsigned int cols,
				      struct input_dev *input_dev)
{
	struct device *dev = input_dev->dev.parent;
	unsigned int row_shift = get_count_order(cols);
	unsigned int max_keys = rows << row_shift;
	u32 *keys;
	int i;
	int size;
	int retval;

	if (!propname)
		propname = "linux,keymap";

	size = device_property_count_u32(dev, propname);
	if (size <= 0) {
		dev_err(dev, "missing or malformed property %s: %d\n",
			propname, size);
		return size < 0 ? size : -EINVAL;
	}

	if (size > max_keys) {
		dev_err(dev, "%s size overflow (%d vs max %u)\n",
			propname, size, max_keys);
		return -EINVAL;
	}

	keys = kmalloc_array(size, sizeof(u32), GFP_KERNEL);
	if (!keys)
		return -ENOMEM;

	retval = device_property_read_u32_array(dev, propname, keys, size);
	if (retval) {
		dev_err(dev, "failed to read %s property: %d\n",
			propname, retval);
		goto out;
	}

	for (i = 0; i < size; i++) {
		if (!matrix_keypad_map_key(input_dev, rows, cols,
					   row_shift, keys[i])) {
			retval = -EINVAL;
			goto out;
		}
	}

	retval = 0;

out:
	kfree(keys);
	return retval;
}