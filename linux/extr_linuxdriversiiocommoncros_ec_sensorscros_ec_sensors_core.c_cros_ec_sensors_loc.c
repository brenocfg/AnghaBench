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
struct cros_ec_sensors_core_state {size_t loc; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 char** cros_ec_loc ; 
 struct cros_ec_sensors_core_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static ssize_t cros_ec_sensors_loc(struct iio_dev *indio_dev,
		uintptr_t private, const struct iio_chan_spec *chan,
		char *buf)
{
	struct cros_ec_sensors_core_state *st = iio_priv(indio_dev);

	return snprintf(buf, PAGE_SIZE, "%s\n", cros_ec_loc[st->loc]);
}