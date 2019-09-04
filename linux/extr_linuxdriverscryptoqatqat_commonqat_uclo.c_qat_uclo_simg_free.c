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
struct icp_qat_fw_loader_handle {TYPE_1__* pci_dev; } ;
struct icp_firml_dram_desc {int /*<<< orphan*/  dram_bus_addr; int /*<<< orphan*/  dram_base_addr_v; scalar_t__ dram_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct icp_firml_dram_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qat_uclo_simg_free(struct icp_qat_fw_loader_handle *handle,
			       struct icp_firml_dram_desc *dram_desc)
{
	dma_free_coherent(&handle->pci_dev->dev,
			  (size_t)(dram_desc->dram_size),
			  (dram_desc->dram_base_addr_v),
			  dram_desc->dram_bus_addr);
	memset(dram_desc, 0, sizeof(*dram_desc));
}