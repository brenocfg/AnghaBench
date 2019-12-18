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
struct spi_device {int /*<<< orphan*/  irq; } ;
struct if_spi_card {int suspended; TYPE_1__* pdata; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  priv; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* teardown ) (struct spi_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_suspend (int /*<<< orphan*/ ) ; 
 struct if_spi_card* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  stub1 (struct spi_device*) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int if_spi_suspend(struct device *dev)
{
	struct spi_device *spi = to_spi_device(dev);
	struct if_spi_card *card = spi_get_drvdata(spi);

	if (!card->suspended) {
		lbs_suspend(card->priv);
		flush_workqueue(card->workqueue);
		disable_irq(spi->irq);

		if (card->pdata->teardown)
			card->pdata->teardown(spi);
		card->suspended = 1;
	}

	return 0;
}