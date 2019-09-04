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

/* Variables and functions */
 int /*<<< orphan*/  at91_adc_trigger_handler ; 
 int /*<<< orphan*/  iio_pollfunc_store_time ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int at91_adc_buffer_init(struct iio_dev *idev)
{
	return iio_triggered_buffer_setup(idev, &iio_pollfunc_store_time,
		&at91_adc_trigger_handler, NULL);
}