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
struct mxt_data {int t19_num_keys; int /*<<< orphan*/ * t19_keymap; TYPE_1__* client; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char const*,int) ; 
 int device_property_count_u32 (struct device*,char const*) ; 
 scalar_t__ device_property_present (struct device*,char const*) ; 
 int device_property_read_u32_array (struct device*,char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * devm_kmalloc_array (struct device*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxt_parse_device_properties(struct mxt_data *data)
{
	static const char keymap_property[] = "linux,gpio-keymap";
	struct device *dev = &data->client->dev;
	u32 *keymap;
	int n_keys;
	int error;

	if (device_property_present(dev, keymap_property)) {
		n_keys = device_property_count_u32(dev, keymap_property);
		if (n_keys <= 0) {
			error = n_keys < 0 ? n_keys : -EINVAL;
			dev_err(dev, "invalid/malformed '%s' property: %d\n",
				keymap_property, error);
			return error;
		}

		keymap = devm_kmalloc_array(dev, n_keys, sizeof(*keymap),
					    GFP_KERNEL);
		if (!keymap)
			return -ENOMEM;

		error = device_property_read_u32_array(dev, keymap_property,
						       keymap, n_keys);
		if (error) {
			dev_err(dev, "failed to parse '%s' property: %d\n",
				keymap_property, error);
			return error;
		}

		data->t19_keymap = keymap;
		data->t19_num_keys = n_keys;
	}

	return 0;
}