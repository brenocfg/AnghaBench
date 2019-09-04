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
struct toshsd_host {scalar_t__ ioaddr; TYPE_1__* pdev; struct mmc_data* data; } ;
struct mmc_data {scalar_t__ error; int bytes_xfered; int blocks; int blksz; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SD_STOPINTERNAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iowrite16 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  toshsd_finish_request (struct toshsd_host*) ; 

__attribute__((used)) static void toshsd_data_end_irq(struct toshsd_host *host)
{
	struct mmc_data *data = host->data;

	host->data = NULL;

	if (!data) {
		dev_warn(&host->pdev->dev, "Spurious data end IRQ\n");
		return;
	}

	if (data->error == 0)
		data->bytes_xfered = data->blocks * data->blksz;
	else
		data->bytes_xfered = 0;

	dev_dbg(&host->pdev->dev, "Completed data request xfr=%d\n",
		data->bytes_xfered);

	iowrite16(0, host->ioaddr + SD_STOPINTERNAL);

	toshsd_finish_request(host);
}