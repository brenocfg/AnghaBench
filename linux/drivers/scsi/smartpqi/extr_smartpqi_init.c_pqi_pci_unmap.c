#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pqi_sg_descriptor {int /*<<< orphan*/  length; int /*<<< orphan*/  address; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int DMA_NONE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 scalar_t__ get_unaligned_le64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pqi_pci_unmap(struct pci_dev *pci_dev,
	struct pqi_sg_descriptor *descriptors, int num_descriptors,
	enum dma_data_direction data_direction)
{
	int i;

	if (data_direction == DMA_NONE)
		return;

	for (i = 0; i < num_descriptors; i++)
		dma_unmap_single(&pci_dev->dev,
			(dma_addr_t)get_unaligned_le64(&descriptors[i].address),
			get_unaligned_le32(&descriptors[i].length),
			data_direction);
}