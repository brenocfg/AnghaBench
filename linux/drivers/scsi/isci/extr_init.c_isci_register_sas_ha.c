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
struct sas_ha_struct {int num_phys; int strict_wide_ports; struct asd_sas_port** sas_port; struct asd_sas_phy** sas_phy; int /*<<< orphan*/ * sas_addr; int /*<<< orphan*/  lldd_module; int /*<<< orphan*/  sas_ha_name; } ;
struct isci_host {struct asd_sas_port* sas_ports; TYPE_2__* phys; TYPE_1__* pdev; struct sas_ha_struct sas_ha; } ;
struct asd_sas_port {int dummy; } ;
struct asd_sas_phy {int dummy; } ;
struct TYPE_4__ {struct asd_sas_phy sas_phy; int /*<<< orphan*/ * sas_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SCI_MAX_PHYS ; 
 int SCI_MAX_PORTS ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 void* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_register_ha (struct sas_ha_struct*) ; 

__attribute__((used)) static int isci_register_sas_ha(struct isci_host *isci_host)
{
	int i;
	struct sas_ha_struct *sas_ha = &(isci_host->sas_ha);
	struct asd_sas_phy **sas_phys;
	struct asd_sas_port **sas_ports;

	sas_phys = devm_kcalloc(&isci_host->pdev->dev,
				SCI_MAX_PHYS, sizeof(void *),
				GFP_KERNEL);
	if (!sas_phys)
		return -ENOMEM;

	sas_ports = devm_kcalloc(&isci_host->pdev->dev,
				 SCI_MAX_PORTS, sizeof(void *),
				 GFP_KERNEL);
	if (!sas_ports)
		return -ENOMEM;

	sas_ha->sas_ha_name = DRV_NAME;
	sas_ha->lldd_module = THIS_MODULE;
	sas_ha->sas_addr    = &isci_host->phys[0].sas_addr[0];

	for (i = 0; i < SCI_MAX_PHYS; i++) {
		sas_phys[i] = &isci_host->phys[i].sas_phy;
		sas_ports[i] = &isci_host->sas_ports[i];
	}

	sas_ha->sas_phy  = sas_phys;
	sas_ha->sas_port = sas_ports;
	sas_ha->num_phys = SCI_MAX_PHYS;

	sas_ha->strict_wide_ports = 1;

	sas_register_ha(sas_ha);

	return 0;
}