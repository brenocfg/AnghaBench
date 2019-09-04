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
struct module {int dummy; } ;
struct iio_trigger {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __iio_trigger_register (struct iio_trigger*,struct module*) ; 
 int /*<<< orphan*/  devm_iio_trigger_unreg ; 
 int /*<<< orphan*/  devres_add (struct device*,struct iio_trigger**) ; 
 struct iio_trigger** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct iio_trigger**) ; 

int __devm_iio_trigger_register(struct device *dev,
				struct iio_trigger *trig_info,
				struct module *this_mod)
{
	struct iio_trigger **ptr;
	int ret;

	ptr = devres_alloc(devm_iio_trigger_unreg, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return -ENOMEM;

	*ptr = trig_info;
	ret = __iio_trigger_register(trig_info, this_mod);
	if (!ret)
		devres_add(dev, ptr);
	else
		devres_free(ptr);

	return ret;
}