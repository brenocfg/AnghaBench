#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u64 ;
typedef  int u16 ;
struct pm8001_ioctl_payload {int minor_function; int length; int* func_specific; scalar_t__ offset; } ;
struct pm8001_hba_info {scalar_t__ chip_id; int* sas_addr; TYPE_2__* phy; TYPE_1__* chip; TYPE_3__* pdev; int /*<<< orphan*/ * nvmd_completion; } ;
struct TYPE_8__ {int (* get_nvmd_req ) (struct pm8001_hba_info*,struct pm8001_ioctl_payload*) ;} ;
struct TYPE_7__ {scalar_t__ subsystem_vendor; } ;
struct TYPE_6__ {int dev_sas_addr; } ;
struct TYPE_5__ {int n_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCI_DEVICE_ID ; 
 scalar_t__ PCI_VENDOR_ID_ATTO ; 
 TYPE_4__* PM8001_CHIP_DISP ; 
 int /*<<< orphan*/  PM8001_INIT_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 scalar_t__ chip_8001 ; 
 scalar_t__ chip_8070 ; 
 scalar_t__ chip_8072 ; 
 int /*<<< orphan*/  completion ; 
 int cpu_to_be64 (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (TYPE_3__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pm8001_printk (char*,...) ; 
 int stub1 (struct pm8001_hba_info*,struct pm8001_ioctl_payload*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pm8001_init_sas_add(struct pm8001_hba_info *pm8001_ha)
{
	u8 i, j;
	u8 sas_add[8];
#ifdef PM8001_READ_VPD
	/* For new SPC controllers WWN is stored in flash vpd
	*  For SPC/SPCve controllers WWN is stored in EEPROM
	*  For Older SPC WWN is stored in NVMD
	*/
	DECLARE_COMPLETION_ONSTACK(completion);
	struct pm8001_ioctl_payload payload;
	u16 deviceid;
	int rc;

	pci_read_config_word(pm8001_ha->pdev, PCI_DEVICE_ID, &deviceid);
	pm8001_ha->nvmd_completion = &completion;

	if (pm8001_ha->chip_id == chip_8001) {
		if (deviceid == 0x8081 || deviceid == 0x0042) {
			payload.minor_function = 4;
			payload.length = 4096;
		} else {
			payload.minor_function = 0;
			payload.length = 128;
		}
	} else if ((pm8001_ha->chip_id == chip_8070 ||
			pm8001_ha->chip_id == chip_8072) &&
			pm8001_ha->pdev->subsystem_vendor == PCI_VENDOR_ID_ATTO) {
		payload.minor_function = 4;
		payload.length = 4096;
	} else {
		payload.minor_function = 1;
		payload.length = 4096;
	}
	payload.offset = 0;
	payload.func_specific = kzalloc(payload.length, GFP_KERNEL);
	if (!payload.func_specific) {
		PM8001_INIT_DBG(pm8001_ha, pm8001_printk("mem alloc fail\n"));
		return;
	}
	rc = PM8001_CHIP_DISP->get_nvmd_req(pm8001_ha, &payload);
	if (rc) {
		kfree(payload.func_specific);
		PM8001_INIT_DBG(pm8001_ha, pm8001_printk("nvmd failed\n"));
		return;
	}
	wait_for_completion(&completion);

	for (i = 0, j = 0; i <= 7; i++, j++) {
		if (pm8001_ha->chip_id == chip_8001) {
			if (deviceid == 0x8081)
				pm8001_ha->sas_addr[j] =
					payload.func_specific[0x704 + i];
			else if (deviceid == 0x0042)
				pm8001_ha->sas_addr[j] =
					payload.func_specific[0x010 + i];
		} else if ((pm8001_ha->chip_id == chip_8070 ||
				pm8001_ha->chip_id == chip_8072) &&
				pm8001_ha->pdev->subsystem_vendor == PCI_VENDOR_ID_ATTO) {
			pm8001_ha->sas_addr[j] =
					payload.func_specific[0x010 + i];
		} else
			pm8001_ha->sas_addr[j] =
					payload.func_specific[0x804 + i];
	}
	memcpy(sas_add, pm8001_ha->sas_addr, SAS_ADDR_SIZE);
	for (i = 0; i < pm8001_ha->chip->n_phy; i++) {
		if (i && ((i % 4) == 0))
			sas_add[7] = sas_add[7] + 4;
		memcpy(&pm8001_ha->phy[i].dev_sas_addr,
			sas_add, SAS_ADDR_SIZE);
		PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("phy %d sas_addr = %016llx\n", i,
			pm8001_ha->phy[i].dev_sas_addr));
	}
	kfree(payload.func_specific);
#else
	for (i = 0; i < pm8001_ha->chip->n_phy; i++) {
		pm8001_ha->phy[i].dev_sas_addr = 0x50010c600047f9d0ULL;
		pm8001_ha->phy[i].dev_sas_addr =
			cpu_to_be64((u64)
				(*(u64 *)&pm8001_ha->phy[i].dev_sas_addr));
	}
	memcpy(pm8001_ha->sas_addr, &pm8001_ha->phy[0].dev_sas_addr,
		SAS_ADDR_SIZE);
#endif
}