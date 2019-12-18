#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sdhci_host {int flags; unsigned int bounce_buffer_size; int quirks; int pending_reset; TYPE_2__* mmc; int /*<<< orphan*/  lock; struct mmc_request** mrqs_done; int /*<<< orphan*/  clock; TYPE_1__* ops; scalar_t__ data_cmd; scalar_t__ cmd; int /*<<< orphan*/  bounce_addr; int /*<<< orphan*/  bounce_buffer; } ;
struct mmc_request {struct mmc_data* data; } ;
struct mmc_data {scalar_t__ host_cookie; unsigned int bytes_xfered; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_clock ) (struct sdhci_host*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ COOKIE_MAPPED ; 
 scalar_t__ COOKIE_UNMAPPED ; 
 scalar_t__ DMA_FROM_DEVICE ; 
 int SDHCI_MAX_MRQS ; 
 int SDHCI_QUIRK_CLOCK_BEFORE_RESET ; 
 int SDHCI_REQ_USE_DMA ; 
 int /*<<< orphan*/  SDHCI_RESET_CMD ; 
 int /*<<< orphan*/  SDHCI_RESET_DATA ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmc_dev (TYPE_2__*) ; 
 scalar_t__ mmc_get_dma_dir (struct mmc_data*) ; 
 int /*<<< orphan*/  mmc_hostname (TYPE_2__*) ; 
 int /*<<< orphan*/  mmc_request_done (TYPE_2__*,struct mmc_request*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sdhci_do_reset (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 scalar_t__ sdhci_needs_reset (struct sdhci_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  sg_copy_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct sdhci_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool sdhci_request_done(struct sdhci_host *host)
{
	unsigned long flags;
	struct mmc_request *mrq;
	int i;

	spin_lock_irqsave(&host->lock, flags);

	for (i = 0; i < SDHCI_MAX_MRQS; i++) {
		mrq = host->mrqs_done[i];
		if (mrq)
			break;
	}

	if (!mrq) {
		spin_unlock_irqrestore(&host->lock, flags);
		return true;
	}

	/*
	 * Always unmap the data buffers if they were mapped by
	 * sdhci_prepare_data() whenever we finish with a request.
	 * This avoids leaking DMA mappings on error.
	 */
	if (host->flags & SDHCI_REQ_USE_DMA) {
		struct mmc_data *data = mrq->data;

		if (data && data->host_cookie == COOKIE_MAPPED) {
			if (host->bounce_buffer) {
				/*
				 * On reads, copy the bounced data into the
				 * sglist
				 */
				if (mmc_get_dma_dir(data) == DMA_FROM_DEVICE) {
					unsigned int length = data->bytes_xfered;

					if (length > host->bounce_buffer_size) {
						pr_err("%s: bounce buffer is %u bytes but DMA claims to have transferred %u bytes\n",
						       mmc_hostname(host->mmc),
						       host->bounce_buffer_size,
						       data->bytes_xfered);
						/* Cap it down and continue */
						length = host->bounce_buffer_size;
					}
					dma_sync_single_for_cpu(
						host->mmc->parent,
						host->bounce_addr,
						host->bounce_buffer_size,
						DMA_FROM_DEVICE);
					sg_copy_from_buffer(data->sg,
						data->sg_len,
						host->bounce_buffer,
						length);
				} else {
					/* No copying, just switch ownership */
					dma_sync_single_for_cpu(
						host->mmc->parent,
						host->bounce_addr,
						host->bounce_buffer_size,
						mmc_get_dma_dir(data));
				}
			} else {
				/* Unmap the raw data */
				dma_unmap_sg(mmc_dev(host->mmc), data->sg,
					     data->sg_len,
					     mmc_get_dma_dir(data));
			}
			data->host_cookie = COOKIE_UNMAPPED;
		}
	}

	/*
	 * The controller needs a reset of internal state machines
	 * upon error conditions.
	 */
	if (sdhci_needs_reset(host, mrq)) {
		/*
		 * Do not finish until command and data lines are available for
		 * reset. Note there can only be one other mrq, so it cannot
		 * also be in mrqs_done, otherwise host->cmd and host->data_cmd
		 * would both be null.
		 */
		if (host->cmd || host->data_cmd) {
			spin_unlock_irqrestore(&host->lock, flags);
			return true;
		}

		/* Some controllers need this kick or reset won't work here */
		if (host->quirks & SDHCI_QUIRK_CLOCK_BEFORE_RESET)
			/* This is to force an update */
			host->ops->set_clock(host, host->clock);

		/* Spec says we should do both at the same time, but Ricoh
		   controllers do not like that. */
		sdhci_do_reset(host, SDHCI_RESET_CMD);
		sdhci_do_reset(host, SDHCI_RESET_DATA);

		host->pending_reset = false;
	}

	host->mrqs_done[i] = NULL;

	spin_unlock_irqrestore(&host->lock, flags);

	mmc_request_done(host->mmc, mrq);

	return false;
}