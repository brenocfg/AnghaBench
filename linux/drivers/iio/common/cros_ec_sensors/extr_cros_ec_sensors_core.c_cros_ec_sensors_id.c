#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
struct TYPE_3__ {int sensor_num; } ;
struct TYPE_4__ {TYPE_1__ info; } ;
struct cros_ec_sensors_core_state {TYPE_2__ param; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct cros_ec_sensors_core_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t cros_ec_sensors_id(struct iio_dev *indio_dev,
				  uintptr_t private,
				  const struct iio_chan_spec *chan, char *buf)
{
	struct cros_ec_sensors_core_state *st = iio_priv(indio_dev);

	return snprintf(buf, PAGE_SIZE, "%d\n", st->param.info.sensor_num);
}