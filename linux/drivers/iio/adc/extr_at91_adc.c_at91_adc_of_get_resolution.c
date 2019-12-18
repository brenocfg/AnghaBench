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
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
struct at91_adc_state {int low_res; int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct iio_dev* iio_priv_to_dev (struct at91_adc_state*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int of_property_count_strings (struct device_node*,char*) ; 
 scalar_t__ of_property_read_string (struct device_node*,char*,char const**) ; 
 scalar_t__ of_property_read_string_index (struct device_node*,char*,int,char const**) ; 
 scalar_t__ of_property_read_u32_array (struct device_node*,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int at91_adc_of_get_resolution(struct at91_adc_state *st,
				      struct platform_device *pdev)
{
	struct iio_dev *idev = iio_priv_to_dev(st);
	struct device_node *np = pdev->dev.of_node;
	int count, i, ret = 0;
	char *res_name, *s;
	u32 *resolutions;

	count = of_property_count_strings(np, "atmel,adc-res-names");
	if (count < 2) {
		dev_err(&idev->dev, "You must specified at least two resolution names for "
				    "adc-res-names property in the DT\n");
		return count;
	}

	resolutions = kmalloc_array(count, sizeof(*resolutions), GFP_KERNEL);
	if (!resolutions)
		return -ENOMEM;

	if (of_property_read_u32_array(np, "atmel,adc-res", resolutions, count)) {
		dev_err(&idev->dev, "Missing adc-res property in the DT.\n");
		ret = -ENODEV;
		goto ret;
	}

	if (of_property_read_string(np, "atmel,adc-use-res", (const char **)&res_name))
		res_name = "highres";

	for (i = 0; i < count; i++) {
		if (of_property_read_string_index(np, "atmel,adc-res-names", i, (const char **)&s))
			continue;

		if (strcmp(res_name, s))
			continue;

		st->res = resolutions[i];
		if (!strcmp(res_name, "lowres"))
			st->low_res = true;
		else
			st->low_res = false;

		dev_info(&idev->dev, "Resolution used: %u bits\n", st->res);
		goto ret;
	}

	dev_err(&idev->dev, "There is no resolution for %s\n", res_name);

ret:
	kfree(resolutions);
	return ret;
}