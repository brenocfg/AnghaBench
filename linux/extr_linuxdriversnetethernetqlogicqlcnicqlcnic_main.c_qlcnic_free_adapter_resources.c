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
struct qlcnic_fw_dump {int /*<<< orphan*/ * tmpl_hdr; int /*<<< orphan*/ * dma_buffer; int /*<<< orphan*/  phys_addr; } ;
struct qlcnic_adapter {TYPE_3__* ahw; TYPE_1__* pdev; int /*<<< orphan*/ * recv_ctx; } ;
struct TYPE_5__ {int /*<<< orphan*/ * buff; } ;
struct TYPE_6__ {struct qlcnic_fw_dump fw_dump; TYPE_2__ reset; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLC_PEX_DMA_READ_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qlcnic_free_adapter_resources(struct qlcnic_adapter *adapter)
{
	struct qlcnic_fw_dump *fw_dump = &adapter->ahw->fw_dump;

	kfree(adapter->recv_ctx);
	adapter->recv_ctx = NULL;

	if (fw_dump->tmpl_hdr) {
		vfree(fw_dump->tmpl_hdr);
		fw_dump->tmpl_hdr = NULL;
	}

	if (fw_dump->dma_buffer) {
		dma_free_coherent(&adapter->pdev->dev, QLC_PEX_DMA_READ_SIZE,
				  fw_dump->dma_buffer, fw_dump->phys_addr);
		fw_dump->dma_buffer = NULL;
	}

	kfree(adapter->ahw->reset.buff);
	adapter->ahw->fw_dump.tmpl_hdr = NULL;
}