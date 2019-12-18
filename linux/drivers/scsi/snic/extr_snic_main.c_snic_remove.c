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
struct snic {int stop_link_events; int in_remove; int /*<<< orphan*/  shost; int /*<<< orphan*/  vdev; int /*<<< orphan*/  list; int /*<<< orphan*/  snic_lock; } ;
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  snic_list_lock; int /*<<< orphan*/  event_q; } ;
struct TYPE_3__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNIC_INFO (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNIC_OFFLINE ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct snic* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snic_cleanup (struct snic*) ; 
 int /*<<< orphan*/  snic_clear_intr_mode (struct snic*) ; 
 int /*<<< orphan*/  snic_del_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snic_disc_term (struct snic*) ; 
 int /*<<< orphan*/  snic_free_intr (struct snic*) ; 
 int /*<<< orphan*/  snic_free_vnic_res (struct snic*) ; 
 TYPE_2__* snic_glob ; 
 int /*<<< orphan*/  snic_iounmap (struct snic*) ; 
 int /*<<< orphan*/  snic_set_state (struct snic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snic_stats_debugfs_remove (struct snic*) ; 
 int /*<<< orphan*/  snic_tgt_del_all (struct snic*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  svnic_dev_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svnic_dev_notify_unset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svnic_dev_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
snic_remove(struct pci_dev *pdev)
{
	struct snic *snic = pci_get_drvdata(pdev);
	unsigned long flags;

	if (!snic) {
		SNIC_INFO("sNIC dev: bus %d slot %d fn %d snic inst is null.\n",
			  pdev->bus->number, PCI_SLOT(pdev->devfn),
			  PCI_FUNC(pdev->devfn));

		return;
	}

	/*
	 * Mark state so that the workqueue thread stops forwarding
	 * received frames and link events. ISR and other threads
	 * that can queue work items will also stop creating work
	 * items on the snic workqueue
	 */
	snic_set_state(snic, SNIC_OFFLINE);
	spin_lock_irqsave(&snic->snic_lock, flags);
	snic->stop_link_events = 1;
	spin_unlock_irqrestore(&snic->snic_lock, flags);

	flush_workqueue(snic_glob->event_q);
	snic_disc_term(snic);

	spin_lock_irqsave(&snic->snic_lock, flags);
	snic->in_remove = 1;
	spin_unlock_irqrestore(&snic->snic_lock, flags);

	/*
	 * This stops the snic device, masks all interrupts, Completed
	 * CQ entries are drained. Posted WQ/RQ/Copy-WQ entries are
	 * cleanup
	 */
	snic_cleanup(snic);

	spin_lock_irqsave(&snic_glob->snic_list_lock, flags);
	list_del(&snic->list);
	spin_unlock_irqrestore(&snic_glob->snic_list_lock, flags);

	snic_tgt_del_all(snic);
#ifdef CONFIG_SCSI_SNIC_DEBUG_FS
	snic_stats_debugfs_remove(snic);
#endif
	snic_del_host(snic->shost);

	svnic_dev_notify_unset(snic->vdev);
	snic_free_intr(snic);
	snic_free_vnic_res(snic);
	snic_clear_intr_mode(snic);
	svnic_dev_close(snic->vdev);
	svnic_dev_unregister(snic->vdev);
	snic_iounmap(snic);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);

	/* this frees Scsi_Host and snic memory (continuous chunk) */
	scsi_host_put(snic->shost);
}