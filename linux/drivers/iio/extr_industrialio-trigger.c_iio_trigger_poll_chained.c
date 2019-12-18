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
struct iio_trigger {scalar_t__ subirq_base; TYPE_1__* subirqs; int /*<<< orphan*/  use_count; } ;
struct TYPE_2__ {scalar_t__ enabled; } ;

/* Variables and functions */
 int CONFIG_IIO_CONSUMERS_PER_TRIGGER ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  handle_nested_irq (scalar_t__) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (struct iio_trigger*) ; 

void iio_trigger_poll_chained(struct iio_trigger *trig)
{
	int i;

	if (!atomic_read(&trig->use_count)) {
		atomic_set(&trig->use_count, CONFIG_IIO_CONSUMERS_PER_TRIGGER);

		for (i = 0; i < CONFIG_IIO_CONSUMERS_PER_TRIGGER; i++) {
			if (trig->subirqs[i].enabled)
				handle_nested_irq(trig->subirq_base + i);
			else
				iio_trigger_notify_done(trig);
		}
	}
}