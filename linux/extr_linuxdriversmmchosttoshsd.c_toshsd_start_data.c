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
struct toshsd_host {scalar_t__ ioaddr; int /*<<< orphan*/  sg_miter; struct mmc_data* data; TYPE_1__* pdev; } ;
struct mmc_data {int flags; int /*<<< orphan*/  blksz; int /*<<< orphan*/  blocks; int /*<<< orphan*/  sg_len; TYPE_2__* sg; } ;
struct TYPE_4__ {int /*<<< orphan*/  offset; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MMC_DATA_READ ; 
 scalar_t__ SD_BLOCKCOUNT ; 
 scalar_t__ SD_CARDXFERDATALEN ; 
 unsigned int SG_MITER_ATOMIC ; 
 unsigned int SG_MITER_FROM_SG ; 
 unsigned int SG_MITER_TO_SG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite16 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sg_miter_start (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void toshsd_start_data(struct toshsd_host *host, struct mmc_data *data)
{
	unsigned int flags = SG_MITER_ATOMIC;

	dev_dbg(&host->pdev->dev, "setup data transfer: blocksize %08x  nr_blocks %d, offset: %08x\n",
		data->blksz, data->blocks, data->sg->offset);

	host->data = data;

	if (data->flags & MMC_DATA_READ)
		flags |= SG_MITER_TO_SG;
	else
		flags |= SG_MITER_FROM_SG;

	sg_miter_start(&host->sg_miter, data->sg, data->sg_len, flags);

	/* Set transfer length and blocksize */
	iowrite16(data->blocks, host->ioaddr + SD_BLOCKCOUNT);
	iowrite16(data->blksz, host->ioaddr + SD_CARDXFERDATALEN);
}