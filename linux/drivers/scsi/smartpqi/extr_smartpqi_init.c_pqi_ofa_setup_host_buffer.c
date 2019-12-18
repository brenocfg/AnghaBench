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
typedef  int /*<<< orphan*/  u32 ;
struct pqi_ofa_memory {int /*<<< orphan*/  bytes_allocated; int /*<<< orphan*/  signature; int /*<<< orphan*/  version; } ;
struct pqi_ctrl_info {struct pqi_ofa_memory* pqi_ofa_mem_virt_addr; int /*<<< orphan*/  pqi_ofa_mem_dma_handle; TYPE_1__* pci_dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PQI_OFA_MEMORY_DESCRIPTOR_LENGTH ; 
 int /*<<< orphan*/  PQI_OFA_SIGNATURE ; 
 int /*<<< orphan*/  PQI_OFA_VERSION ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct pqi_ofa_memory* dma_alloc_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pqi_ofa_alloc_host_buffer (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pqi_ofa_setup_host_buffer(struct pqi_ctrl_info *ctrl_info,
	u32 bytes_requested)
{
	struct pqi_ofa_memory *pqi_ofa_memory;
	struct device *dev;

	dev = &ctrl_info->pci_dev->dev;
	pqi_ofa_memory = dma_alloc_coherent(dev,
					    PQI_OFA_MEMORY_DESCRIPTOR_LENGTH,
					    &ctrl_info->pqi_ofa_mem_dma_handle,
					    GFP_KERNEL);

	if (!pqi_ofa_memory)
		return;

	put_unaligned_le16(PQI_OFA_VERSION, &pqi_ofa_memory->version);
	memcpy(&pqi_ofa_memory->signature, PQI_OFA_SIGNATURE,
					sizeof(pqi_ofa_memory->signature));
	pqi_ofa_memory->bytes_allocated = cpu_to_le32(bytes_requested);

	ctrl_info->pqi_ofa_mem_virt_addr = pqi_ofa_memory;

	if (pqi_ofa_alloc_host_buffer(ctrl_info) < 0) {
		dev_err(dev, "Failed to allocate host buffer of size = %u",
			bytes_requested);
	}
}