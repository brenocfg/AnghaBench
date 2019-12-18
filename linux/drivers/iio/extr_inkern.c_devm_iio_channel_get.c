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
 int /*<<< orphan*/  devm_iio_channel_free ; 
 int /*<<< orphan*/  devres_add (struct device*,struct iio_channel**) ; 
 struct iio_channel** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct iio_channel**) ; 
 struct iio_channel* iio_channel_get (struct device*,char const*) ; 

struct iio_channel *devm_iio_channel_get(struct device *dev,
					 const char *channel_name)
{
	struct iio_channel **ptr, *channel;

	ptr = devres_alloc(devm_iio_channel_free, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	channel = iio_channel_get(dev, channel_name);
	if (IS_ERR(channel)) {
		devres_free(ptr);
		return channel;
	}

	*ptr = channel;
	devres_add(dev, ptr);

	return channel;
}