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
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct at91_adc_state {int /*<<< orphan*/  trig; TYPE_1__* selected_trig; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_adc_allocate_trigger (struct iio_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct at91_adc_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int at91_adc_trigger_init(struct iio_dev *indio)
{
	struct at91_adc_state *st = iio_priv(indio);

	st->trig = at91_adc_allocate_trigger(indio, st->selected_trig->name);
	if (IS_ERR(st->trig)) {
		dev_err(&indio->dev,
			"could not allocate trigger\n");
		return PTR_ERR(st->trig);
	}

	return 0;
}