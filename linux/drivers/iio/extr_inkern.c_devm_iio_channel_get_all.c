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
struct iio_channel {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct iio_channel* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct iio_channel*) ; 
 int /*<<< orphan*/  devm_iio_channel_free_all ; 
 int /*<<< orphan*/  devres_add (struct device*,struct iio_channel**) ; 
 struct iio_channel** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct iio_channel**) ; 
 struct iio_channel* iio_channel_get_all (struct device*) ; 

struct iio_channel *devm_iio_channel_get_all(struct device *dev)
{
	struct iio_channel **ptr, *channels;

	ptr = devres_alloc(devm_iio_channel_free_all, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	channels = iio_channel_get_all(dev);
	if (IS_ERR(channels)) {
		devres_free(ptr);
		return channels;
	}

	*ptr = channels;
	devres_add(dev, ptr);

	return channels;
}