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
struct ssp_data {int shut_down; TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq_wake (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ssp_enable_mcu(struct ssp_data *data, bool enable)
{
	dev_info(&data->spi->dev, "current shutdown = %d, old = %d\n", enable,
		 data->shut_down);

	if (enable && data->shut_down) {
		data->shut_down = false;
		enable_irq(data->spi->irq);
		enable_irq_wake(data->spi->irq);
	} else if (!enable && !data->shut_down) {
		data->shut_down = true;
		disable_irq(data->spi->irq);
		disable_irq_wake(data->spi->irq);
	} else {
		dev_warn(&data->spi->dev, "current shutdown = %d, old = %d\n",
			 enable, data->shut_down);
	}
}