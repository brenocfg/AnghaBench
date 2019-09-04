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
struct at91_adc_state {int trigger_number; int /*<<< orphan*/ * trig; } ;

/* Variables and functions */
 struct at91_adc_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void at91_adc_trigger_remove(struct iio_dev *idev)
{
	struct at91_adc_state *st = iio_priv(idev);
	int i;

	for (i = 0; i < st->trigger_number; i++) {
		iio_trigger_unregister(st->trig[i]);
		iio_trigger_free(st->trig[i]);
	}
}