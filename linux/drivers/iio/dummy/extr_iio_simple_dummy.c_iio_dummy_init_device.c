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
struct iio_dummy_state {int single_ended_adc_val; int* differential_adc_val; int accel_val; int accel_calibbias; int steps; int activity_running; int activity_walking; int /*<<< orphan*/ * accel_calibscale; scalar_t__ dac_val; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * dummy_scales ; 
 struct iio_dummy_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int iio_dummy_init_device(struct iio_dev *indio_dev)
{
	struct iio_dummy_state *st = iio_priv(indio_dev);

	st->dac_val = 0;
	st->single_ended_adc_val = 73;
	st->differential_adc_val[0] = 33;
	st->differential_adc_val[1] = -34;
	st->accel_val = 34;
	st->accel_calibbias = -7;
	st->accel_calibscale = &dummy_scales[0];
	st->steps = 47;
	st->activity_running = 98;
	st->activity_walking = 4;

	return 0;
}