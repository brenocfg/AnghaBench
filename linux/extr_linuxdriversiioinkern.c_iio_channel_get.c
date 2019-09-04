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
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 char* dev_name (struct device*) ; 
 struct iio_channel* iio_channel_get_sys (char const*,char const*) ; 
 struct iio_channel* of_iio_channel_get_by_name (int /*<<< orphan*/ ,char const*) ; 

struct iio_channel *iio_channel_get(struct device *dev,
				    const char *channel_name)
{
	const char *name = dev ? dev_name(dev) : NULL;
	struct iio_channel *channel;

	if (dev) {
		channel = of_iio_channel_get_by_name(dev->of_node,
						     channel_name);
		if (channel != NULL)
			return channel;
	}

	return iio_channel_get_sys(name, channel_name);
}