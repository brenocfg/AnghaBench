#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct spi_device {TYPE_2__ dev; } ;
struct ads7846 {struct ads7846* packet; int /*<<< orphan*/  filter_data; int /*<<< orphan*/  (* filter_cleanup ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  gpio_pendown; int /*<<< orphan*/  get_pendown_state; int /*<<< orphan*/  reg; int /*<<< orphan*/  input; TYPE_1__* spi; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ads7846_disable (struct ads7846*) ; 
 int /*<<< orphan*/  ads784x_attr_group ; 
 int /*<<< orphan*/  ads784x_hwmon_unregister (struct spi_device*,struct ads7846*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ads7846*) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ads7846*) ; 
 int /*<<< orphan*/  regulator_put (int /*<<< orphan*/ ) ; 
 struct ads7846* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ads7846_remove(struct spi_device *spi)
{
	struct ads7846 *ts = spi_get_drvdata(spi);

	sysfs_remove_group(&spi->dev.kobj, &ads784x_attr_group);

	ads7846_disable(ts);
	free_irq(ts->spi->irq, ts);

	input_unregister_device(ts->input);

	ads784x_hwmon_unregister(spi, ts);

	regulator_put(ts->reg);

	if (!ts->get_pendown_state) {
		/*
		 * If we are not using specialized pendown method we must
		 * have been relying on gpio we set up ourselves.
		 */
		gpio_free(ts->gpio_pendown);
	}

	if (ts->filter_cleanup)
		ts->filter_cleanup(ts->filter_data);

	kfree(ts->packet);
	kfree(ts);

	dev_dbg(&spi->dev, "unregistered touchscreen\n");

	return 0;
}