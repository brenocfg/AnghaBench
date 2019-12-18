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
struct sg_mapping_iter {unsigned short* addr; int length; int consumed; } ;
struct toshsd_host {int /*<<< orphan*/  lock; scalar_t__ ioaddr; TYPE_2__* pdev; TYPE_1__* cmd; struct sg_mapping_iter sg_miter; struct mmc_data* data; } ;
struct mmc_data {int blksz; int flags; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int MMC_DATA_READ ; 
 scalar_t__ SD_DATAPORT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ioread32_rep (scalar_t__,unsigned short*,int) ; 
 int /*<<< orphan*/  iowrite32_rep (scalar_t__,unsigned short*,int) ; 
 int /*<<< orphan*/  sg_miter_next (struct sg_mapping_iter*) ; 
 int /*<<< orphan*/  sg_miter_stop (struct sg_mapping_iter*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  toshsd_finish_request (struct toshsd_host*) ; 

__attribute__((used)) static irqreturn_t toshsd_thread_irq(int irq, void *dev_id)
{
	struct toshsd_host *host = dev_id;
	struct mmc_data *data = host->data;
	struct sg_mapping_iter *sg_miter = &host->sg_miter;
	unsigned short *buf;
	int count;
	unsigned long flags;

	if (!data) {
		dev_warn(&host->pdev->dev, "Spurious Data IRQ\n");
		if (host->cmd) {
			host->cmd->error = -EIO;
			toshsd_finish_request(host);
		}
		return IRQ_NONE;
	}
	spin_lock_irqsave(&host->lock, flags);

	if (!sg_miter_next(sg_miter))
		goto done;

	buf = sg_miter->addr;

	/* Ensure we dont read more than one block. The chip will interrupt us
	 * When the next block is available.
	 */
	count = sg_miter->length;
	if (count > data->blksz)
		count = data->blksz;

	dev_dbg(&host->pdev->dev, "count: %08x, flags %08x\n", count,
		data->flags);

	/* Transfer the data */
	if (data->flags & MMC_DATA_READ)
		ioread32_rep(host->ioaddr + SD_DATAPORT, buf, count >> 2);
	else
		iowrite32_rep(host->ioaddr + SD_DATAPORT, buf, count >> 2);

	sg_miter->consumed = count;
	sg_miter_stop(sg_miter);

done:
	spin_unlock_irqrestore(&host->lock, flags);

	return IRQ_HANDLED;
}