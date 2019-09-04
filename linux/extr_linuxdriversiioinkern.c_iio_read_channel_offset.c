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
 int /*<<< orphan*/  IIO_CHAN_INFO_OFFSET ; 
 int iio_read_channel_attribute (struct iio_channel*,int*,int*,int /*<<< orphan*/ ) ; 

int iio_read_channel_offset(struct iio_channel *chan, int *val, int *val2)
{
	return iio_read_channel_attribute(chan, val, val2, IIO_CHAN_INFO_OFFSET);
}