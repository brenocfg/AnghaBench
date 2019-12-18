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
struct scatterlist {int dummy; } ;
struct rtsx_pcr {TYPE_1__* pci; scalar_t__ remove_pci; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 int EINVAL ; 
 int dma_map_sg (int /*<<< orphan*/ *,struct scatterlist*,int,int) ; 

int rtsx_pci_dma_map_sg(struct rtsx_pcr *pcr, struct scatterlist *sglist,
		int num_sg, bool read)
{
	enum dma_data_direction dir = read ? DMA_FROM_DEVICE : DMA_TO_DEVICE;

	if (pcr->remove_pci)
		return -EINVAL;

	if ((sglist == NULL) || (num_sg <= 0))
		return -EINVAL;

	return dma_map_sg(&(pcr->pci->dev), sglist, num_sg, dir);
}