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
struct itg3200 {int /*<<< orphan*/  trig; TYPE_1__* i2c; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct itg3200* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_unregister (int /*<<< orphan*/ ) ; 

void itg3200_remove_trigger(struct iio_dev *indio_dev)
{
	struct itg3200 *st = iio_priv(indio_dev);

	iio_trigger_unregister(st->trig);
	free_irq(st->i2c->irq, st->trig);
	iio_trigger_free(st->trig);
}