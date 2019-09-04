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
struct tifm_sd {int /*<<< orphan*/  cmd_flags; TYPE_2__* req; } ;
struct tifm_dev {int /*<<< orphan*/  lock; scalar_t__ addr; int /*<<< orphan*/  dev; } ;
struct mmc_host {int dummy; } ;
struct mmc_data {int dummy; } ;
struct TYPE_4__ {TYPE_1__* cmd; } ;
struct TYPE_3__ {struct mmc_data* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIFO_READY ; 
 scalar_t__ SOCK_DMA_FIFO_STATUS ; 
 unsigned int TIFM_FIFO_READY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,int /*<<< orphan*/ ) ; 
 struct tifm_sd* mmc_priv (struct mmc_host*) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ tifm_get_drvdata (struct tifm_dev*) ; 
 int /*<<< orphan*/  tifm_sd_check_status (struct tifm_sd*) ; 
 scalar_t__ tifm_sd_set_dma_data (struct tifm_sd*,struct mmc_data*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void tifm_sd_data_event(struct tifm_dev *sock)
{
	struct tifm_sd *host;
	unsigned int fifo_status = 0;
	struct mmc_data *r_data = NULL;

	spin_lock(&sock->lock);
	host = mmc_priv((struct mmc_host*)tifm_get_drvdata(sock));
	fifo_status = readl(sock->addr + SOCK_DMA_FIFO_STATUS);
	dev_dbg(&sock->dev, "data event: fifo_status %x, flags %x\n",
		fifo_status, host->cmd_flags);

	if (host->req) {
		r_data = host->req->cmd->data;

		if (r_data && (fifo_status & TIFM_FIFO_READY)) {
			if (tifm_sd_set_dma_data(host, r_data)) {
				host->cmd_flags |= FIFO_READY;
				tifm_sd_check_status(host);
			}
		}
	}

	writel(fifo_status, sock->addr + SOCK_DMA_FIFO_STATUS);
	spin_unlock(&sock->lock);
}