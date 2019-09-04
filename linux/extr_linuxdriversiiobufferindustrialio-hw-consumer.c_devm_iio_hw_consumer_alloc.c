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
struct iio_hw_consumer {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct iio_hw_consumer*) ; 
 int /*<<< orphan*/  devm_iio_hw_consumer_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct iio_hw_consumer**) ; 
 struct iio_hw_consumer** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct iio_hw_consumer**) ; 
 struct iio_hw_consumer* iio_hw_consumer_alloc (struct device*) ; 

struct iio_hw_consumer *devm_iio_hw_consumer_alloc(struct device *dev)
{
	struct iio_hw_consumer **ptr, *iio_hwc;

	ptr = devres_alloc(devm_iio_hw_consumer_release, sizeof(*ptr),
			   GFP_KERNEL);
	if (!ptr)
		return NULL;

	iio_hwc = iio_hw_consumer_alloc(dev);
	if (IS_ERR(iio_hwc)) {
		devres_free(ptr);
	} else {
		*ptr = iio_hwc;
		devres_add(dev, ptr);
	}

	return iio_hwc;
}