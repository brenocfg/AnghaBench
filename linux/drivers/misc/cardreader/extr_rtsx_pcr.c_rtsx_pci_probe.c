#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct rtsx_pcr {int id; int rtsx_resv_buf_addr; int host_cmds_addr; int host_sg_tbl_addr; int msi_en; int /*<<< orphan*/  remap_addr; int /*<<< orphan*/ * rtsx_resv_buf; struct pci_dev* pci; int /*<<< orphan*/  irq; int /*<<< orphan*/  idle_work; int /*<<< orphan*/  carddet_work; scalar_t__ card_removed; scalar_t__ card_inserted; int /*<<< orphan*/ * host_sg_tbl_ptr; int /*<<< orphan*/ * host_cmds_ptr; struct rtsx_pcr* pcr; } ;
struct pcr_handle {int id; int rtsx_resv_buf_addr; int host_cmds_addr; int host_sg_tbl_addr; int msi_en; int /*<<< orphan*/  remap_addr; int /*<<< orphan*/ * rtsx_resv_buf; struct pci_dev* pci; int /*<<< orphan*/  irq; int /*<<< orphan*/  idle_work; int /*<<< orphan*/  carddet_work; scalar_t__ card_removed; scalar_t__ card_inserted; int /*<<< orphan*/ * host_sg_tbl_ptr; int /*<<< orphan*/ * host_cmds_ptr; struct pcr_handle* pcr; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; scalar_t__ revision; scalar_t__ device; scalar_t__ vendor; } ;
struct TYPE_4__ {int pdata_size; struct rtsx_pcr* platform_data; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ CHK_PCI_PID (struct rtsx_pcr*,int) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_NAME_RTSX_PCI ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int HOST_CMDS_BUF_LEN ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTSX_RESV_BUF_LEN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct rtsx_pcr*) ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rtsx_pcr*) ; 
 struct rtsx_pcr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mfd_add_devices (int /*<<< orphan*/ *,int,TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int msi_en ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int pci_enable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int rtsx_pci_acquire_irq (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rtsx_pci_card_detect ; 
 int /*<<< orphan*/  rtsx_pci_idle_work ; 
 int /*<<< orphan*/  rtsx_pci_idr ; 
 int rtsx_pci_init_chip (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rtsx_pci_lock ; 
 TYPE_1__* rtsx_pcr_cells ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtsx_pci_probe(struct pci_dev *pcidev,
			  const struct pci_device_id *id)
{
	struct rtsx_pcr *pcr;
	struct pcr_handle *handle;
	u32 base, len;
	int ret, i, bar = 0;

	dev_dbg(&(pcidev->dev),
		": Realtek PCI-E Card Reader found at %s [%04x:%04x] (rev %x)\n",
		pci_name(pcidev), (int)pcidev->vendor, (int)pcidev->device,
		(int)pcidev->revision);

	ret = pci_set_dma_mask(pcidev, DMA_BIT_MASK(32));
	if (ret < 0)
		return ret;

	ret = pci_enable_device(pcidev);
	if (ret)
		return ret;

	ret = pci_request_regions(pcidev, DRV_NAME_RTSX_PCI);
	if (ret)
		goto disable;

	pcr = kzalloc(sizeof(*pcr), GFP_KERNEL);
	if (!pcr) {
		ret = -ENOMEM;
		goto release_pci;
	}

	handle = kzalloc(sizeof(*handle), GFP_KERNEL);
	if (!handle) {
		ret = -ENOMEM;
		goto free_pcr;
	}
	handle->pcr = pcr;

	idr_preload(GFP_KERNEL);
	spin_lock(&rtsx_pci_lock);
	ret = idr_alloc(&rtsx_pci_idr, pcr, 0, 0, GFP_NOWAIT);
	if (ret >= 0)
		pcr->id = ret;
	spin_unlock(&rtsx_pci_lock);
	idr_preload_end();
	if (ret < 0)
		goto free_handle;

	pcr->pci = pcidev;
	dev_set_drvdata(&pcidev->dev, handle);

	if (CHK_PCI_PID(pcr, 0x525A))
		bar = 1;
	len = pci_resource_len(pcidev, bar);
	base = pci_resource_start(pcidev, bar);
	pcr->remap_addr = ioremap_nocache(base, len);
	if (!pcr->remap_addr) {
		ret = -ENOMEM;
		goto free_handle;
	}

	pcr->rtsx_resv_buf = dma_alloc_coherent(&(pcidev->dev),
			RTSX_RESV_BUF_LEN, &(pcr->rtsx_resv_buf_addr),
			GFP_KERNEL);
	if (pcr->rtsx_resv_buf == NULL) {
		ret = -ENXIO;
		goto unmap;
	}
	pcr->host_cmds_ptr = pcr->rtsx_resv_buf;
	pcr->host_cmds_addr = pcr->rtsx_resv_buf_addr;
	pcr->host_sg_tbl_ptr = pcr->rtsx_resv_buf + HOST_CMDS_BUF_LEN;
	pcr->host_sg_tbl_addr = pcr->rtsx_resv_buf_addr + HOST_CMDS_BUF_LEN;

	pcr->card_inserted = 0;
	pcr->card_removed = 0;
	INIT_DELAYED_WORK(&pcr->carddet_work, rtsx_pci_card_detect);
	INIT_DELAYED_WORK(&pcr->idle_work, rtsx_pci_idle_work);

	pcr->msi_en = msi_en;
	if (pcr->msi_en) {
		ret = pci_enable_msi(pcidev);
		if (ret)
			pcr->msi_en = false;
	}

	ret = rtsx_pci_acquire_irq(pcr);
	if (ret < 0)
		goto disable_msi;

	pci_set_master(pcidev);
	synchronize_irq(pcr->irq);

	ret = rtsx_pci_init_chip(pcr);
	if (ret < 0)
		goto disable_irq;

	for (i = 0; i < ARRAY_SIZE(rtsx_pcr_cells); i++) {
		rtsx_pcr_cells[i].platform_data = handle;
		rtsx_pcr_cells[i].pdata_size = sizeof(*handle);
	}
	ret = mfd_add_devices(&pcidev->dev, pcr->id, rtsx_pcr_cells,
			ARRAY_SIZE(rtsx_pcr_cells), NULL, 0, NULL);
	if (ret < 0)
		goto disable_irq;

	schedule_delayed_work(&pcr->idle_work, msecs_to_jiffies(200));

	return 0;

disable_irq:
	free_irq(pcr->irq, (void *)pcr);
disable_msi:
	if (pcr->msi_en)
		pci_disable_msi(pcr->pci);
	dma_free_coherent(&(pcr->pci->dev), RTSX_RESV_BUF_LEN,
			pcr->rtsx_resv_buf, pcr->rtsx_resv_buf_addr);
unmap:
	iounmap(pcr->remap_addr);
free_handle:
	kfree(handle);
free_pcr:
	kfree(pcr);
release_pci:
	pci_release_regions(pcidev);
disable:
	pci_disable_device(pcidev);

	return ret;
}