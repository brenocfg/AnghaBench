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
typedef  scalar_t__ u32 ;
struct si1133_data {scalar_t__ scan_mask; int /*<<< orphan*/  completion; int /*<<< orphan*/  regmap; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SI1133_REG_IRQ_STATUS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ *,char*) ; 
 struct si1133_data* iio_priv (struct iio_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static irqreturn_t si1133_threaded_irq_handler(int irq, void *private)
{
	struct iio_dev *iio_dev = private;
	struct si1133_data *data = iio_priv(iio_dev);
	u32 irq_status;
	int err;

	err = regmap_read(data->regmap, SI1133_REG_IRQ_STATUS, &irq_status);
	if (err) {
		dev_err_ratelimited(&iio_dev->dev, "Error reading IRQ\n");
		goto out;
	}

	if (irq_status != data->scan_mask)
		return IRQ_NONE;

out:
	complete(&data->completion);

	return IRQ_HANDLED;
}