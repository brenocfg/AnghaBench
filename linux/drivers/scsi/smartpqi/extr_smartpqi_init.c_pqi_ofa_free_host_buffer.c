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
struct pqi_sg_descriptor {int /*<<< orphan*/  address; int /*<<< orphan*/  length; } ;
struct pqi_ofa_memory {int /*<<< orphan*/  num_memory_descriptors; struct pqi_sg_descriptor* sg_descriptor; int /*<<< orphan*/  bytes_allocated; } ;
struct pqi_ctrl_info {struct pqi_ofa_memory* pqi_ofa_mem_virt_addr; int /*<<< orphan*/  pqi_ofa_mem_dma_handle; TYPE_1__* pci_dev; struct pqi_ofa_memory** pqi_ofa_chunk_virt_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PQI_OFA_MEMORY_DESCRIPTOR_LENGTH ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pqi_ofa_memory*,int /*<<< orphan*/ ) ; 
 int get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_unaligned_le64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pqi_ofa_memory**) ; 

__attribute__((used)) static void pqi_ofa_free_host_buffer(struct pqi_ctrl_info *ctrl_info)
{
	int i;
	struct pqi_sg_descriptor *mem_descriptor;
	struct pqi_ofa_memory *ofap;

	ofap = ctrl_info->pqi_ofa_mem_virt_addr;

	if (!ofap)
		return;

	if (!ofap->bytes_allocated)
		goto out;

	mem_descriptor = ofap->sg_descriptor;

	for (i = 0; i < get_unaligned_le16(&ofap->num_memory_descriptors);
		i++) {
		dma_free_coherent(&ctrl_info->pci_dev->dev,
			get_unaligned_le32(&mem_descriptor[i].length),
			ctrl_info->pqi_ofa_chunk_virt_addr[i],
			get_unaligned_le64(&mem_descriptor[i].address));
	}
	kfree(ctrl_info->pqi_ofa_chunk_virt_addr);

out:
	dma_free_coherent(&ctrl_info->pci_dev->dev,
			PQI_OFA_MEMORY_DESCRIPTOR_LENGTH, ofap,
			ctrl_info->pqi_ofa_mem_dma_handle);
	ctrl_info->pqi_ofa_mem_virt_addr = NULL;
}