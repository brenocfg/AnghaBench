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
struct iio_dev {int /*<<< orphan*/ * setup_ops; int /*<<< orphan*/  dev; } ;
struct at91_adc_state {TYPE_1__* selected_trig; } ;
struct TYPE_2__ {scalar_t__ hw_trig; } ;

/* Variables and functions */
 int /*<<< orphan*/  at91_adc_trigger_handler ; 
 int /*<<< orphan*/  at91_buffer_setup_ops ; 
 int devm_iio_triggered_buffer_setup (int /*<<< orphan*/ *,struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_pollfunc_store_time ; 
 struct at91_adc_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int at91_adc_buffer_init(struct iio_dev *indio)
{
	struct at91_adc_state *st = iio_priv(indio);

	if (st->selected_trig->hw_trig) {
		return devm_iio_triggered_buffer_setup(&indio->dev, indio,
			&iio_pollfunc_store_time,
			&at91_adc_trigger_handler, &at91_buffer_setup_ops);
	}
	/*
	 * we need to prepare the buffer ops in case we will get
	 * another buffer attached (like a callback buffer for the touchscreen)
	 */
	indio->setup_ops = &at91_buffer_setup_ops;

	return 0;
}