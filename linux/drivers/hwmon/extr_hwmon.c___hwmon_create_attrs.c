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
struct hwmon_chip_info {scalar_t__* info; int /*<<< orphan*/  ops; } ;
struct device {int dummy; } ;
struct attribute {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct attribute** ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct attribute** devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int hwmon_genattrs (struct device*,void const*,struct attribute**,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ hwmon_num_channel_attrs (scalar_t__) ; 

__attribute__((used)) static struct attribute **
__hwmon_create_attrs(struct device *dev, const void *drvdata,
		     const struct hwmon_chip_info *chip)
{
	int ret, i, aindex = 0, nattrs = 0;
	struct attribute **attrs;

	for (i = 0; chip->info[i]; i++)
		nattrs += hwmon_num_channel_attrs(chip->info[i]);

	if (nattrs == 0)
		return ERR_PTR(-EINVAL);

	attrs = devm_kcalloc(dev, nattrs + 1, sizeof(*attrs), GFP_KERNEL);
	if (!attrs)
		return ERR_PTR(-ENOMEM);

	for (i = 0; chip->info[i]; i++) {
		ret = hwmon_genattrs(dev, drvdata, &attrs[aindex], chip->ops,
				     chip->info[i]);
		if (ret < 0)
			return ERR_PTR(ret);
		aindex += ret;
	}

	return attrs;
}