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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
struct cros_ec_accel_legacy_state {size_t sensor_num; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 size_t MOTIONSENSE_LOC_BASE ; 
 char** cros_ec_accel_legacy_loc_strings ; 
 struct cros_ec_accel_legacy_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t cros_ec_accel_legacy_loc(struct iio_dev *indio_dev,
					uintptr_t private,
					const struct iio_chan_spec *chan,
					char *buf)
{
	struct cros_ec_accel_legacy_state *st = iio_priv(indio_dev);

	return sprintf(buf, "%s\n",
		       cros_ec_accel_legacy_loc_strings[st->sensor_num +
							MOTIONSENSE_LOC_BASE]);
}