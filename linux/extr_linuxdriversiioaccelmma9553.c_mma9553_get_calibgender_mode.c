#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  filter; } ;
struct mma9553_data {TYPE_1__ conf; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMA9553_MASK_CONF_MALE ; 
 struct mma9553_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mma9553_get_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mma9553_get_calibgender_mode(struct iio_dev *indio_dev,
					const struct iio_chan_spec *chan)
{
	struct mma9553_data *data = iio_priv(indio_dev);
	u8 gender;

	gender = mma9553_get_bits(data->conf.filter, MMA9553_MASK_CONF_MALE);
	/*
	 * HW expects 0 for female and 1 for male,
	 * while iio index is 0 for male and 1 for female.
	 */
	return !gender;
}