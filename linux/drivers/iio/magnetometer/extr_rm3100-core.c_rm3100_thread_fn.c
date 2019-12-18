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
struct rm3100_data {int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  RM3100_REG_POLL ; 
 struct rm3100_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t rm3100_thread_fn(int irq, void *d)
{
	struct iio_dev *indio_dev = d;
	struct rm3100_data *data = iio_priv(indio_dev);

	/*
	 * Write operation to any register or read operation
	 * to first byte of results will clear the interrupt.
	 */
	regmap_write(data->regmap, RM3100_REG_POLL, 0);

	return IRQ_HANDLED;
}