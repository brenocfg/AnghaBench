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

/* Variables and functions */
 int /*<<< orphan*/  IIO_CHAN_INFO_RAW ; 
 int iio_write_channel_attribute (struct iio_channel*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int iio_write_channel_raw(struct iio_channel *chan, int val)
{
	return iio_write_channel_attribute(chan, val, 0, IIO_CHAN_INFO_RAW);
}