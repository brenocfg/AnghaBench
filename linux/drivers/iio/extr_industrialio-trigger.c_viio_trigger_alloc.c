#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_5__ {int /*<<< orphan*/ * bus; int /*<<< orphan*/ * type; } ;
struct TYPE_4__ {int /*<<< orphan*/ * irq_unmask; int /*<<< orphan*/ * irq_mask; int /*<<< orphan*/ * name; } ;
struct iio_trigger {scalar_t__ subirq_base; TYPE_2__ dev; TYPE_1__ subirq_chip; int /*<<< orphan*/ * name; int /*<<< orphan*/  pool_lock; } ;

/* Variables and functions */
 int CONFIG_IIO_CONSUMERS_PER_TRIGGER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQ_NOAUTOEN ; 
 int /*<<< orphan*/  IRQ_NOPROBE ; 
 int IRQ_NOREQUEST ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 
 int /*<<< orphan*/  get_device (TYPE_2__*) ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int /*<<< orphan*/  iio_bus_type ; 
 int /*<<< orphan*/  iio_trig_subirqmask ; 
 int /*<<< orphan*/  iio_trig_subirqunmask ; 
 int /*<<< orphan*/  iio_trig_type ; 
 scalar_t__ irq_alloc_descs (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_free_descs (scalar_t__,int) ; 
 int /*<<< orphan*/  irq_modify_status (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  irq_set_handler (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct iio_trigger*) ; 
 int /*<<< orphan*/ * kvasprintf (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 struct iio_trigger* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct iio_trigger *viio_trigger_alloc(const char *fmt, va_list vargs)
{
	struct iio_trigger *trig;
	int i;

	trig = kzalloc(sizeof *trig, GFP_KERNEL);
	if (!trig)
		return NULL;

	trig->dev.type = &iio_trig_type;
	trig->dev.bus = &iio_bus_type;
	device_initialize(&trig->dev);

	mutex_init(&trig->pool_lock);
	trig->subirq_base = irq_alloc_descs(-1, 0,
					    CONFIG_IIO_CONSUMERS_PER_TRIGGER,
					    0);
	if (trig->subirq_base < 0)
		goto free_trig;

	trig->name = kvasprintf(GFP_KERNEL, fmt, vargs);
	if (trig->name == NULL)
		goto free_descs;

	trig->subirq_chip.name = trig->name;
	trig->subirq_chip.irq_mask = &iio_trig_subirqmask;
	trig->subirq_chip.irq_unmask = &iio_trig_subirqunmask;
	for (i = 0; i < CONFIG_IIO_CONSUMERS_PER_TRIGGER; i++) {
		irq_set_chip(trig->subirq_base + i, &trig->subirq_chip);
		irq_set_handler(trig->subirq_base + i, &handle_simple_irq);
		irq_modify_status(trig->subirq_base + i,
				  IRQ_NOREQUEST | IRQ_NOAUTOEN, IRQ_NOPROBE);
	}
	get_device(&trig->dev);

	return trig;

free_descs:
	irq_free_descs(trig->subirq_base, CONFIG_IIO_CONSUMERS_PER_TRIGGER);
free_trig:
	kfree(trig);
	return NULL;
}