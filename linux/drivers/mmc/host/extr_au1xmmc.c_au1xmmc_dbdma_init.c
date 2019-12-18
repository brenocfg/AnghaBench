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
struct resource {int start; } ;
struct au1xmmc_host {int flags; void* rx_chan; void* tx_chan; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU1XMMC_DESCRIPTOR_COUNT ; 
 int ENODEV ; 
 int HOST_F_DBDMA ; 
 int HOST_F_DMA ; 
 int /*<<< orphan*/  IORESOURCE_DMA ; 
 int /*<<< orphan*/  au1xmmc_dbdma_callback ; 
 void* au1xxx_dbdma_chan_alloc (int,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  au1xxx_dbdma_chan_free (void*) ; 
 int /*<<< orphan*/  au1xxx_dbdma_ring_alloc (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au1xxx_dbdma_set_devwidth (void*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int memid ; 
 struct resource* platform_get_resource (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int au1xmmc_dbdma_init(struct au1xmmc_host *host)
{
	struct resource *res;
	int txid, rxid;

	res = platform_get_resource(host->pdev, IORESOURCE_DMA, 0);
	if (!res)
		return -ENODEV;
	txid = res->start;

	res = platform_get_resource(host->pdev, IORESOURCE_DMA, 1);
	if (!res)
		return -ENODEV;
	rxid = res->start;

	if (!memid)
		return -ENODEV;

	host->tx_chan = au1xxx_dbdma_chan_alloc(memid, txid,
				au1xmmc_dbdma_callback, (void *)host);
	if (!host->tx_chan) {
		dev_err(&host->pdev->dev, "cannot allocate TX DMA\n");
		return -ENODEV;
	}

	host->rx_chan = au1xxx_dbdma_chan_alloc(rxid, memid,
				au1xmmc_dbdma_callback, (void *)host);
	if (!host->rx_chan) {
		dev_err(&host->pdev->dev, "cannot allocate RX DMA\n");
		au1xxx_dbdma_chan_free(host->tx_chan);
		return -ENODEV;
	}

	au1xxx_dbdma_set_devwidth(host->tx_chan, 8);
	au1xxx_dbdma_set_devwidth(host->rx_chan, 8);

	au1xxx_dbdma_ring_alloc(host->tx_chan, AU1XMMC_DESCRIPTOR_COUNT);
	au1xxx_dbdma_ring_alloc(host->rx_chan, AU1XMMC_DESCRIPTOR_COUNT);

	/* DBDMA is good to go */
	host->flags |= HOST_F_DMA | HOST_F_DBDMA;

	return 0;
}