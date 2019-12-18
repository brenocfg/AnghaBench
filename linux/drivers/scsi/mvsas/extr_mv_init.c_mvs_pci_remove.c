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
struct sas_ha_struct {struct sas_ha_struct* sas_port; struct sas_ha_struct* sas_phy; scalar_t__ lldd_ha; } ;
struct pci_dev {int dummy; } ;
struct mvs_prv_info {unsigned short n_host; struct mvs_info** mvi; int /*<<< orphan*/  mv_tasklet; } ;
struct mvs_info {TYPE_1__* pdev; int /*<<< orphan*/  shost; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* interrupt_disable ) (struct mvs_info*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 TYPE_2__* MVS_CHIP_DISP ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct sas_ha_struct*) ; 
 int /*<<< orphan*/  kfree (struct sas_ha_struct*) ; 
 int /*<<< orphan*/  mvs_free (struct mvs_info*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct sas_ha_struct* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  sas_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_unregister_ha (struct sas_ha_struct*) ; 
 int /*<<< orphan*/  stub1 (struct mvs_info*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mvs_pci_remove(struct pci_dev *pdev)
{
	unsigned short core_nr, i = 0;
	struct sas_ha_struct *sha = pci_get_drvdata(pdev);
	struct mvs_info *mvi = NULL;

	core_nr = ((struct mvs_prv_info *)sha->lldd_ha)->n_host;
	mvi = ((struct mvs_prv_info *)sha->lldd_ha)->mvi[0];

#ifdef CONFIG_SCSI_MVSAS_TASKLET
	tasklet_kill(&((struct mvs_prv_info *)sha->lldd_ha)->mv_tasklet);
#endif

	sas_unregister_ha(sha);
	sas_remove_host(mvi->shost);

	MVS_CHIP_DISP->interrupt_disable(mvi);
	free_irq(mvi->pdev->irq, sha);
	for (i = 0; i < core_nr; i++) {
		mvi = ((struct mvs_prv_info *)sha->lldd_ha)->mvi[i];
		mvs_free(mvi);
	}
	kfree(sha->sas_phy);
	kfree(sha->sas_port);
	kfree(sha);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	return;
}