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
struct tifm_sd {int /*<<< orphan*/  bounce_buf; scalar_t__ no_dma; struct mmc_request* req; int /*<<< orphan*/  timer; struct tifm_dev* dev; } ;
struct tifm_dev {int /*<<< orphan*/  lock; scalar_t__ addr; int /*<<< orphan*/  dev; } ;
struct mmc_request {TYPE_1__* cmd; } ;
struct mmc_host {int dummy; } ;
struct mmc_data {int flags; int sg_len; int bytes_xfered; int blocks; int blksz; int /*<<< orphan*/ * sg; } ;
struct TYPE_2__ {struct mmc_data* data; } ;

/* Variables and functions */
 int MMC_DATA_WRITE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 scalar_t__ SOCK_CONTROL ; 
 scalar_t__ SOCK_MMCSD_BLOCK_LEN ; 
 scalar_t__ SOCK_MMCSD_INT_ENABLE ; 
 scalar_t__ SOCK_MMCSD_NUM_BLOCKS ; 
 int TIFM_CTRL_LED ; 
 int TIFM_MMCSD_BUFINT ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_request_done (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mmc_host* tifm_get_drvdata (struct tifm_dev*) ; 
 int /*<<< orphan*/  tifm_unmap_sg (struct tifm_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void tifm_sd_end_cmd(unsigned long data)
{
	struct tifm_sd *host = (struct tifm_sd*)data;
	struct tifm_dev *sock = host->dev;
	struct mmc_host *mmc = tifm_get_drvdata(sock);
	struct mmc_request *mrq;
	struct mmc_data *r_data = NULL;
	unsigned long flags;

	spin_lock_irqsave(&sock->lock, flags);

	del_timer(&host->timer);
	mrq = host->req;
	host->req = NULL;

	if (!mrq) {
		pr_err(" %s : no request to complete?\n",
		       dev_name(&sock->dev));
		spin_unlock_irqrestore(&sock->lock, flags);
		return;
	}

	r_data = mrq->cmd->data;
	if (r_data) {
		if (host->no_dma) {
			writel((~TIFM_MMCSD_BUFINT)
			       & readl(sock->addr + SOCK_MMCSD_INT_ENABLE),
			       sock->addr + SOCK_MMCSD_INT_ENABLE);
		} else {
			tifm_unmap_sg(sock, &host->bounce_buf, 1,
				      (r_data->flags & MMC_DATA_WRITE)
				      ? PCI_DMA_TODEVICE : PCI_DMA_FROMDEVICE);
			tifm_unmap_sg(sock, r_data->sg, r_data->sg_len,
				      (r_data->flags & MMC_DATA_WRITE)
				      ? PCI_DMA_TODEVICE : PCI_DMA_FROMDEVICE);
		}

		r_data->bytes_xfered = r_data->blocks
			- readl(sock->addr + SOCK_MMCSD_NUM_BLOCKS) - 1;
		r_data->bytes_xfered *= r_data->blksz;
		r_data->bytes_xfered += r_data->blksz
			- readl(sock->addr + SOCK_MMCSD_BLOCK_LEN) + 1;
	}

	writel((~TIFM_CTRL_LED) & readl(sock->addr + SOCK_CONTROL),
	       sock->addr + SOCK_CONTROL);

	spin_unlock_irqrestore(&sock->lock, flags);
	mmc_request_done(mmc, mrq);
}