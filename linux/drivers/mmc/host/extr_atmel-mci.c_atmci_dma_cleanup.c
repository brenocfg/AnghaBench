#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mmc_data {int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct TYPE_6__ {TYPE_2__* chan; } ;
struct atmel_mci {TYPE_3__ dma; struct mmc_data* data; } ;
struct TYPE_5__ {TYPE_1__* device; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_get_dma_dir (struct mmc_data*) ; 

__attribute__((used)) static void atmci_dma_cleanup(struct atmel_mci *host)
{
	struct mmc_data                 *data = host->data;

	if (data)
		dma_unmap_sg(host->dma.chan->device->dev,
				data->sg, data->sg_len,
				mmc_get_dma_dir(data));
}