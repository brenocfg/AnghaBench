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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pa_tx; int /*<<< orphan*/ * va_tx; int /*<<< orphan*/  pa_rx; int /*<<< orphan*/  va_rx; } ;
struct cfspi {int /*<<< orphan*/  wq; int /*<<< orphan*/  wait; int /*<<< orphan*/  state; TYPE_1__ xfer; int /*<<< orphan*/ * ndev; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_TERMINATE ; 
 int /*<<< orphan*/  cfspi_list_lock ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_debugfs_rem (struct cfspi*) ; 
 int /*<<< orphan*/  dma_free (struct cfspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct cfspi* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cfspi_uninit(struct net_device *dev)
{
	struct cfspi *cfspi = netdev_priv(dev);

	/* Remove from list. */
	spin_lock(&cfspi_list_lock);
	list_del(&cfspi->list);
	spin_unlock(&cfspi_list_lock);

	cfspi->ndev = NULL;
	/* Free DMA buffers. */
	dma_free(cfspi, cfspi->xfer.va_rx, cfspi->xfer.pa_rx);
	dma_free(cfspi, cfspi->xfer.va_tx[0], cfspi->xfer.pa_tx[0]);
	set_bit(SPI_TERMINATE, &cfspi->state);
	wake_up_interruptible(&cfspi->wait);
	destroy_workqueue(cfspi->wq);
	/* Destroy debugfs directory and files. */
	dev_debugfs_rem(cfspi);
	return;
}