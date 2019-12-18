#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  mbox64_t ;
struct TYPE_6__ {int flag; int /*<<< orphan*/  una_mbox64_dma; int /*<<< orphan*/  una_mbox64; int /*<<< orphan*/  dev; int /*<<< orphan*/  scb_list; int /*<<< orphan*/  buf_dma_handle; int /*<<< orphan*/  mega_buffer; TYPE_1__* host; scalar_t__ base; } ;
typedef  TYPE_2__ adapter_t ;
struct TYPE_5__ {int host_no; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int BOARD_MEMMAP ; 
 int MEGA_BUFFER_SIZE ; 
 int /*<<< orphan*/  __megaraid_shutdown (TYPE_2__*) ; 
 int /*<<< orphan*/  hba_count ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mega_free_sgl (TYPE_2__*) ; 
 int /*<<< orphan*/  mega_proc_dir_entry ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 
 int /*<<< orphan*/  remove_proc_subtree (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void
megaraid_remove_one(struct pci_dev *pdev)
{
	struct Scsi_Host *host = pci_get_drvdata(pdev);
	adapter_t *adapter = (adapter_t *)host->hostdata;
	char buf[12] = { 0 };

	scsi_remove_host(host);

	__megaraid_shutdown(adapter);

	/* Free our resources */
	if (adapter->flag & BOARD_MEMMAP) {
		iounmap((void *)adapter->base);
		release_mem_region(adapter->host->base, 128);
	} else
		release_region(adapter->base, 16);

	mega_free_sgl(adapter);

	sprintf(buf, "hba%d", adapter->host->host_no);
	remove_proc_subtree(buf, mega_proc_dir_entry);

	pci_free_consistent(adapter->dev, MEGA_BUFFER_SIZE,
			adapter->mega_buffer, adapter->buf_dma_handle);
	kfree(adapter->scb_list);
	pci_free_consistent(adapter->dev, sizeof(mbox64_t),
			adapter->una_mbox64, adapter->una_mbox64_dma);

	scsi_host_put(host);
	pci_disable_device(pdev);

	hba_count--;
}