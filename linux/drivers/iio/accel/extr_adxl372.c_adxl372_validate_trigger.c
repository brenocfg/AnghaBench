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
struct iio_trigger {int dummy; } ;
struct iio_dev {int dummy; } ;
struct adxl372_state {struct iio_trigger* dready_trig; } ;

/* Variables and functions */
 int EINVAL ; 
 struct adxl372_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int adxl372_validate_trigger(struct iio_dev *indio_dev,
				    struct iio_trigger *trig)
{
	struct adxl372_state *st = iio_priv(indio_dev);

	if (st->dready_trig != trig)
		return -EINVAL;

	return 0;
}