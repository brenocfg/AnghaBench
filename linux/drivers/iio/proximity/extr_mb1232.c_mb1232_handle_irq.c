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
struct mb1232_data {int /*<<< orphan*/  ranging; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct mb1232_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static irqreturn_t mb1232_handle_irq(int irq, void *dev_id)
{
	struct iio_dev *indio_dev = dev_id;
	struct mb1232_data *data = iio_priv(indio_dev);

	complete(&data->ranging);

	return IRQ_HANDLED;
}