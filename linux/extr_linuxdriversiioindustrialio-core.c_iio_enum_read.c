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
struct iio_enum {int (* get ) (struct iio_dev*,struct iio_chan_spec const*) ;int num_items; char** items; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int stub1 (struct iio_dev*,struct iio_chan_spec const*) ; 

ssize_t iio_enum_read(struct iio_dev *indio_dev,
	uintptr_t priv, const struct iio_chan_spec *chan, char *buf)
{
	const struct iio_enum *e = (const struct iio_enum *)priv;
	int i;

	if (!e->get)
		return -EINVAL;

	i = e->get(indio_dev, chan);
	if (i < 0)
		return i;
	else if (i >= e->num_items)
		return -EINVAL;

	return snprintf(buf, PAGE_SIZE, "%s\n", e->items[i]);
}