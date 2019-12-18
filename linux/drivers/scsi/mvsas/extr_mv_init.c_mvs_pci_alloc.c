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
struct sas_ha_struct {scalar_t__ lldd_ha; } ;
struct pci_device_id {size_t driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct mvs_slot_info {int dummy; } ;
struct mvs_prv_info {int /*<<< orphan*/  n_phy; struct mvs_info** mvi; } ;
struct mvs_info {size_t chip_id; unsigned int id; void* tags; struct Scsi_Host* shost; struct sas_ha_struct* sas; TYPE_1__* chip; int /*<<< orphan*/  wq_list; int /*<<< orphan*/ * dev; struct pci_dev* pdev; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_4__ {scalar_t__ (* chip_ioremap ) (struct mvs_info*) ;} ;
struct TYPE_3__ {long slot_width; int /*<<< orphan*/  n_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_2__* MVS_CHIP_DISP ; 
 int MVS_CHIP_SLOT_SZ ; 
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_alloc (struct mvs_info*,struct Scsi_Host*) ; 
 TYPE_1__* mvs_chips ; 
 int /*<<< orphan*/  mvs_free (struct mvs_info*) ; 
 scalar_t__ stub1 (struct mvs_info*) ; 

__attribute__((used)) static struct mvs_info *mvs_pci_alloc(struct pci_dev *pdev,
				const struct pci_device_id *ent,
				struct Scsi_Host *shost, unsigned int id)
{
	struct mvs_info *mvi = NULL;
	struct sas_ha_struct *sha = SHOST_TO_SAS_HA(shost);

	mvi = kzalloc(sizeof(*mvi) +
		(1L << mvs_chips[ent->driver_data].slot_width) *
		sizeof(struct mvs_slot_info), GFP_KERNEL);
	if (!mvi)
		return NULL;

	mvi->pdev = pdev;
	mvi->dev = &pdev->dev;
	mvi->chip_id = ent->driver_data;
	mvi->chip = &mvs_chips[mvi->chip_id];
	INIT_LIST_HEAD(&mvi->wq_list);

	((struct mvs_prv_info *)sha->lldd_ha)->mvi[id] = mvi;
	((struct mvs_prv_info *)sha->lldd_ha)->n_phy = mvi->chip->n_phy;

	mvi->id = id;
	mvi->sas = sha;
	mvi->shost = shost;

	mvi->tags = kzalloc(MVS_CHIP_SLOT_SZ>>3, GFP_KERNEL);
	if (!mvi->tags)
		goto err_out;

	if (MVS_CHIP_DISP->chip_ioremap(mvi))
		goto err_out;
	if (!mvs_alloc(mvi, shost))
		return mvi;
err_out:
	mvs_free(mvi);
	return NULL;
}