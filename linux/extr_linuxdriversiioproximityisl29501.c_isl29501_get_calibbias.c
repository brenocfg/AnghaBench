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
struct isl29501_private {int dummy; } ;
struct iio_chan_spec {int type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_PROXIMITY 129 
#define  IIO_TEMP 128 
 int /*<<< orphan*/  REG_DISTANCE_BIAS ; 
 int /*<<< orphan*/  REG_TEMPERATURE_BIAS ; 
 int isl29501_register_read (struct isl29501_private*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int isl29501_get_calibbias(struct isl29501_private *isl29501,
				  const struct iio_chan_spec *chan,
				  int *bias)
{
	switch (chan->type) {
	case IIO_PROXIMITY:
		return isl29501_register_read(isl29501,
					      REG_DISTANCE_BIAS,
					      bias);
	case IIO_TEMP:
		return isl29501_register_read(isl29501,
					      REG_TEMPERATURE_BIAS,
					      bias);
	default:
		return -EINVAL;
	}
}