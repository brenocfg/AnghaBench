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
struct st_i2c_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  sda_min_width_us; int /*<<< orphan*/  scl_min_width_us; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int st_i2c_of_get_deglitch(struct device_node *np,
		struct st_i2c_dev *i2c_dev)
{
	int ret;

	ret = of_property_read_u32(np, "st,i2c-min-scl-pulse-width-us",
			&i2c_dev->scl_min_width_us);
	if ((ret == -ENODATA) || (ret == -EOVERFLOW)) {
		dev_err(i2c_dev->dev, "st,i2c-min-scl-pulse-width-us invalid\n");
		return ret;
	}

	ret = of_property_read_u32(np, "st,i2c-min-sda-pulse-width-us",
			&i2c_dev->sda_min_width_us);
	if ((ret == -ENODATA) || (ret == -EOVERFLOW)) {
		dev_err(i2c_dev->dev, "st,i2c-min-sda-pulse-width-us invalid\n");
		return ret;
	}

	return 0;
}