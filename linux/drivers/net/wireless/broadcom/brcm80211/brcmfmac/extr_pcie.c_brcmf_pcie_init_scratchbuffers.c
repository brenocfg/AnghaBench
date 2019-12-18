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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ tcm_base_address; scalar_t__ ringupd_dmahandle; void* ringupd; scalar_t__ scratch_dmahandle; void* scratch; } ;
struct brcmf_pciedev_info {TYPE_2__ shared; TYPE_1__* pdev; } ;
struct brcmf_bus {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BRCMF_DMA_D2H_RINGUPD_BUF_LEN ; 
 int BRCMF_DMA_D2H_SCRATCH_BUF_LEN ; 
 scalar_t__ BRCMF_SHARED_DMA_RINGUPD_ADDR_OFFSET ; 
 scalar_t__ BRCMF_SHARED_DMA_RINGUPD_LEN_OFFSET ; 
 scalar_t__ BRCMF_SHARED_DMA_SCRATCH_ADDR_OFFSET ; 
 scalar_t__ BRCMF_SHARED_DMA_SCRATCH_LEN_OFFSET ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  brcmf_err (struct brcmf_bus*,char*) ; 
 int /*<<< orphan*/  brcmf_pcie_release_scratchbuffers (struct brcmf_pciedev_info*) ; 
 int /*<<< orphan*/  brcmf_pcie_write_tcm32 (struct brcmf_pciedev_info*,scalar_t__,int) ; 
 struct brcmf_bus* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmf_pcie_init_scratchbuffers(struct brcmf_pciedev_info *devinfo)
{
	struct brcmf_bus *bus = dev_get_drvdata(&devinfo->pdev->dev);
	u64 address;
	u32 addr;

	devinfo->shared.scratch =
		dma_alloc_coherent(&devinfo->pdev->dev,
				   BRCMF_DMA_D2H_SCRATCH_BUF_LEN,
				   &devinfo->shared.scratch_dmahandle,
				   GFP_KERNEL);
	if (!devinfo->shared.scratch)
		goto fail;

	addr = devinfo->shared.tcm_base_address +
	       BRCMF_SHARED_DMA_SCRATCH_ADDR_OFFSET;
	address = (u64)devinfo->shared.scratch_dmahandle;
	brcmf_pcie_write_tcm32(devinfo, addr, address & 0xffffffff);
	brcmf_pcie_write_tcm32(devinfo, addr + 4, address >> 32);
	addr = devinfo->shared.tcm_base_address +
	       BRCMF_SHARED_DMA_SCRATCH_LEN_OFFSET;
	brcmf_pcie_write_tcm32(devinfo, addr, BRCMF_DMA_D2H_SCRATCH_BUF_LEN);

	devinfo->shared.ringupd =
		dma_alloc_coherent(&devinfo->pdev->dev,
				   BRCMF_DMA_D2H_RINGUPD_BUF_LEN,
				   &devinfo->shared.ringupd_dmahandle,
				   GFP_KERNEL);
	if (!devinfo->shared.ringupd)
		goto fail;

	addr = devinfo->shared.tcm_base_address +
	       BRCMF_SHARED_DMA_RINGUPD_ADDR_OFFSET;
	address = (u64)devinfo->shared.ringupd_dmahandle;
	brcmf_pcie_write_tcm32(devinfo, addr, address & 0xffffffff);
	brcmf_pcie_write_tcm32(devinfo, addr + 4, address >> 32);
	addr = devinfo->shared.tcm_base_address +
	       BRCMF_SHARED_DMA_RINGUPD_LEN_OFFSET;
	brcmf_pcie_write_tcm32(devinfo, addr, BRCMF_DMA_D2H_RINGUPD_BUF_LEN);
	return 0;

fail:
	brcmf_err(bus, "Allocating scratch buffers failed\n");
	brcmf_pcie_release_scratchbuffers(devinfo);
	return -ENOMEM;
}