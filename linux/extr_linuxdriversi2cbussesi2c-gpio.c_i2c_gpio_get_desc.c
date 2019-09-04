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
struct gpio_desc {int dummy; } ;
struct device {int dummy; } ;
typedef  enum gpiod_flags { ____Placeholder_gpiod_flags } gpiod_flags ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int EPROBE_DEFER ; 
 struct gpio_desc* ERR_PTR (int) ; 
 int /*<<< orphan*/  IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct gpio_desc* devm_gpiod_get (struct device*,char const*,int) ; 
 struct gpio_desc* devm_gpiod_get_index (struct device*,int /*<<< orphan*/ *,unsigned int,int) ; 

__attribute__((used)) static struct gpio_desc *i2c_gpio_get_desc(struct device *dev,
					   const char *con_id,
					   unsigned int index,
					   enum gpiod_flags gflags)
{
	struct gpio_desc *retdesc;
	int ret;

	retdesc = devm_gpiod_get(dev, con_id, gflags);
	if (!IS_ERR(retdesc)) {
		dev_dbg(dev, "got GPIO from name %s\n", con_id);
		return retdesc;
	}

	retdesc = devm_gpiod_get_index(dev, NULL, index, gflags);
	if (!IS_ERR(retdesc)) {
		dev_dbg(dev, "got GPIO from index %u\n", index);
		return retdesc;
	}

	ret = PTR_ERR(retdesc);

	/* FIXME: hack in the old code, is this really necessary? */
	if (ret == -EINVAL)
		retdesc = ERR_PTR(-EPROBE_DEFER);

	/* This happens if the GPIO driver is not yet probed, let's defer */
	if (ret == -ENOENT)
		retdesc = ERR_PTR(-EPROBE_DEFER);

	if (ret != -EPROBE_DEFER)
		dev_err(dev, "error trying to get descriptor: %d\n", ret);

	return retdesc;
}