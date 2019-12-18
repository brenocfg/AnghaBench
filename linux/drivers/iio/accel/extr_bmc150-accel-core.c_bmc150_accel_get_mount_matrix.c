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
struct iio_mount_matrix {int dummy; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
struct bmc150_accel_data {struct iio_mount_matrix const orientation; } ;

/* Variables and functions */
 struct bmc150_accel_data* iio_priv (struct iio_dev const*) ; 

__attribute__((used)) static const struct iio_mount_matrix *
bmc150_accel_get_mount_matrix(const struct iio_dev *indio_dev,
				const struct iio_chan_spec *chan)
{
	struct bmc150_accel_data *data = iio_priv(indio_dev);

	return &data->orientation;
}