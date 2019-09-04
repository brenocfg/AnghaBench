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
struct iio_trigger {struct iio_trigger* name; scalar_t__ subirq_base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int CONFIG_IIO_CONSUMERS_PER_TRIGGER ; 
 int /*<<< orphan*/  IRQ_NOAUTOEN ; 
 int IRQ_NOPROBE ; 
 int IRQ_NOREQUEST ; 
 int /*<<< orphan*/  irq_free_descs (scalar_t__,int) ; 
 int /*<<< orphan*/  irq_modify_status (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  irq_set_chip (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_handler (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct iio_trigger*) ; 
 struct iio_trigger* to_iio_trigger (struct device*) ; 

__attribute__((used)) static void iio_trig_release(struct device *device)
{
	struct iio_trigger *trig = to_iio_trigger(device);
	int i;

	if (trig->subirq_base) {
		for (i = 0; i < CONFIG_IIO_CONSUMERS_PER_TRIGGER; i++) {
			irq_modify_status(trig->subirq_base + i,
					  IRQ_NOAUTOEN,
					  IRQ_NOREQUEST | IRQ_NOPROBE);
			irq_set_chip(trig->subirq_base + i,
				     NULL);
			irq_set_handler(trig->subirq_base + i,
					NULL);
		}

		irq_free_descs(trig->subirq_base,
			       CONFIG_IIO_CONSUMERS_PER_TRIGGER);
	}
	kfree(trig->name);
	kfree(trig);
}