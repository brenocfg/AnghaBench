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
struct TYPE_5__ {int max_scbs; int num_phys; int enabled_phys; TYPE_1__* phy_desc; int /*<<< orphan*/  max_ddbs; } ;
struct asd_ha_struct {size_t revision_id; TYPE_2__ hw_prof; TYPE_3__* pcidev; } ;
struct TYPE_6__ {size_t revision; } ;
struct TYPE_4__ {void* min_sata_lrate; void* max_sata_lrate; void* min_sas_lrate; int /*<<< orphan*/  max_sas_lrate; } ;

/* Variables and functions */
 size_t AIC9410_DEV_REV_B0 ; 
 int /*<<< orphan*/  ASD_MAX_DDBS ; 
 int ASD_MAX_PHYS ; 
 int ENODEV ; 
 void* SAS_LINK_RATE_1_5_GBPS ; 
 int /*<<< orphan*/  SAS_LINK_RATE_3_0_GBPS ; 
 int /*<<< orphan*/ * asd_dev_rev ; 
 int /*<<< orphan*/  asd_printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  pci_name (TYPE_3__*) ; 

__attribute__((used)) static int asd_common_setup(struct asd_ha_struct *asd_ha)
{
	int err, i;

	asd_ha->revision_id = asd_ha->pcidev->revision;

	err = -ENODEV;
	if (asd_ha->revision_id < AIC9410_DEV_REV_B0) {
		asd_printk("%s is revision %s (%X), which is not supported\n",
			   pci_name(asd_ha->pcidev),
			   asd_dev_rev[asd_ha->revision_id],
			   asd_ha->revision_id);
		goto Err;
	}
	/* Provide some sane default values. */
	asd_ha->hw_prof.max_scbs = 512;
	asd_ha->hw_prof.max_ddbs = ASD_MAX_DDBS;
	asd_ha->hw_prof.num_phys = ASD_MAX_PHYS;
	/* All phys are enabled, by default. */
	asd_ha->hw_prof.enabled_phys = 0xFF;
	for (i = 0; i < ASD_MAX_PHYS; i++) {
		asd_ha->hw_prof.phy_desc[i].max_sas_lrate =
			SAS_LINK_RATE_3_0_GBPS;
		asd_ha->hw_prof.phy_desc[i].min_sas_lrate =
			SAS_LINK_RATE_1_5_GBPS;
		asd_ha->hw_prof.phy_desc[i].max_sata_lrate =
			SAS_LINK_RATE_1_5_GBPS;
		asd_ha->hw_prof.phy_desc[i].min_sata_lrate =
			SAS_LINK_RATE_1_5_GBPS;
	}

	return 0;
Err:
	return err;
}