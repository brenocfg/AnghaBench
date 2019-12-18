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
 int /*<<< orphan*/  iio_channel_release (struct iio_channel*) ; 

__attribute__((used)) static void devm_iio_channel_free(struct device *dev, void *res)
{
	struct iio_channel *channel = *(struct iio_channel **)res;

	iio_channel_release(channel);
}