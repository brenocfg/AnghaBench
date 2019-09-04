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
struct rtsx_pcr {int remove_pci; struct rtsx_pcr* slots; int /*<<< orphan*/  id; int /*<<< orphan*/  remap_addr; TYPE_1__* pci; scalar_t__ msi_en; int /*<<< orphan*/  irq; int /*<<< orphan*/  rtsx_resv_buf_addr; int /*<<< orphan*/  rtsx_resv_buf; int /*<<< orphan*/  idle_work; int /*<<< orphan*/  carddet_work; int /*<<< orphan*/  lock; scalar_t__ bier; struct rtsx_pcr* pcr; } ;
struct pcr_handle {int remove_pci; struct pcr_handle* slots; int /*<<< orphan*/  id; int /*<<< orphan*/  remap_addr; TYPE_1__* pci; scalar_t__ msi_en; int /*<<< orphan*/  irq; int /*<<< orphan*/  rtsx_resv_buf_addr; int /*<<< orphan*/  rtsx_resv_buf; int /*<<< orphan*/  idle_work; int /*<<< orphan*/  carddet_work; int /*<<< orphan*/  lock; scalar_t__ bier; struct pcr_handle* pcr; } ;
struct pci_dev {scalar_t__ device; scalar_t__ vendor; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTSX_BIER ; 
 int /*<<< orphan*/  RTSX_RESV_BUF_LEN ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_1__*) ; 
 struct rtsx_pcr* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  rtsx_pci_idr ; 
 int /*<<< orphan*/  rtsx_pci_lock ; 
 int /*<<< orphan*/  rtsx_pci_writel (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtsx_pci_remove(struct pci_dev *pcidev)
{
	struct pcr_handle *handle = pci_get_drvdata(pcidev);
	struct rtsx_pcr *pcr = handle->pcr;

	pcr->remove_pci = true;

	/* Disable interrupts at the pcr level */
	spin_lock_irq(&pcr->lock);
	rtsx_pci_writel(pcr, RTSX_BIER, 0);
	pcr->bier = 0;
	spin_unlock_irq(&pcr->lock);

	cancel_delayed_work_sync(&pcr->carddet_work);
	cancel_delayed_work_sync(&pcr->idle_work);

	mfd_remove_devices(&pcidev->dev);

	dma_free_coherent(&(pcr->pci->dev), RTSX_RESV_BUF_LEN,
			pcr->rtsx_resv_buf, pcr->rtsx_resv_buf_addr);
	free_irq(pcr->irq, (void *)pcr);
	if (pcr->msi_en)
		pci_disable_msi(pcr->pci);
	iounmap(pcr->remap_addr);

	pci_release_regions(pcidev);
	pci_disable_device(pcidev);

	spin_lock(&rtsx_pci_lock);
	idr_remove(&rtsx_pci_idr, pcr->id);
	spin_unlock(&rtsx_pci_lock);

	kfree(pcr->slots);
	kfree(pcr);
	kfree(handle);

	dev_dbg(&(pcidev->dev),
		": Realtek PCI-E Card Reader at %s [%04x:%04x] has been removed\n",
		pci_name(pcidev), (int)pcidev->vendor, (int)pcidev->device);
}