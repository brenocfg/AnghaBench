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
struct atlas_data {int /*<<< orphan*/  work; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct atlas_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  irq_work_queue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t atlas_interrupt_handler(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct atlas_data *data = iio_priv(indio_dev);

	irq_work_queue(&data->work);

	return IRQ_HANDLED;
}