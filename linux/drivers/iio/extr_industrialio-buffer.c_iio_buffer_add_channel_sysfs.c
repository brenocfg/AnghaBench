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
struct iio_dev {int /*<<< orphan*/  dev; struct iio_buffer* buffer; } ;
struct iio_chan_spec {scalar_t__ type; int /*<<< orphan*/  scan_index; } ;
struct iio_buffer {int /*<<< orphan*/  scan_el_dev_attr_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  IIO_SEPARATE ; 
 scalar_t__ IIO_TIMESTAMP ; 
 int __iio_add_chan_devattr (char*,struct iio_chan_spec const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_scan_el_show ; 
 int /*<<< orphan*/  iio_scan_el_store ; 
 int /*<<< orphan*/  iio_scan_el_ts_show ; 
 int /*<<< orphan*/  iio_scan_el_ts_store ; 
 int /*<<< orphan*/  iio_show_fixed_type ; 
 int /*<<< orphan*/  iio_show_scan_index ; 

__attribute__((used)) static int iio_buffer_add_channel_sysfs(struct iio_dev *indio_dev,
					const struct iio_chan_spec *chan)
{
	int ret, attrcount = 0;
	struct iio_buffer *buffer = indio_dev->buffer;

	ret = __iio_add_chan_devattr("index",
				     chan,
				     &iio_show_scan_index,
				     NULL,
				     0,
				     IIO_SEPARATE,
				     &indio_dev->dev,
				     &buffer->scan_el_dev_attr_list);
	if (ret)
		return ret;
	attrcount++;
	ret = __iio_add_chan_devattr("type",
				     chan,
				     &iio_show_fixed_type,
				     NULL,
				     0,
				     0,
				     &indio_dev->dev,
				     &buffer->scan_el_dev_attr_list);
	if (ret)
		return ret;
	attrcount++;
	if (chan->type != IIO_TIMESTAMP)
		ret = __iio_add_chan_devattr("en",
					     chan,
					     &iio_scan_el_show,
					     &iio_scan_el_store,
					     chan->scan_index,
					     0,
					     &indio_dev->dev,
					     &buffer->scan_el_dev_attr_list);
	else
		ret = __iio_add_chan_devattr("en",
					     chan,
					     &iio_scan_el_ts_show,
					     &iio_scan_el_ts_store,
					     chan->scan_index,
					     0,
					     &indio_dev->dev,
					     &buffer->scan_el_dev_attr_list);
	if (ret)
		return ret;
	attrcount++;
	ret = attrcount;
	return ret;
}