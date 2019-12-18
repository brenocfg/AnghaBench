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
struct megasas_instance {scalar_t__ adapter_type; TYPE_2__* reg_set; int /*<<< orphan*/  ld_ids; scalar_t__ peerIsPresent; scalar_t__ requestorId; TYPE_1__* pdev; int /*<<< orphan*/  adprecovery; } ;
struct TYPE_4__ {int /*<<< orphan*/  inbound_doorbell; int /*<<< orphan*/  doorbell; } ;
struct TYPE_3__ {scalar_t__ device; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEGASAS_HW_CRITICAL_ERROR ; 
 int /*<<< orphan*/  MEGASAS_MAX_LD_IDS ; 
 scalar_t__ MFI_SERIES ; 
 int /*<<< orphan*/  MFI_STOP_ADP ; 
 scalar_t__ PCI_DEVICE_ID_LSI_SAS0071SKINNY ; 
 scalar_t__ PCI_DEVICE_ID_LSI_SAS0073SKINNY ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  megasas_complete_outstanding_ioctls (struct megasas_instance*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void megaraid_sas_kill_hba(struct megasas_instance *instance)
{
	/* Set critical error to block I/O & ioctls in case caller didn't */
	atomic_set(&instance->adprecovery, MEGASAS_HW_CRITICAL_ERROR);
	/* Wait 1 second to ensure IO or ioctls in build have posted */
	msleep(1000);
	if ((instance->pdev->device == PCI_DEVICE_ID_LSI_SAS0073SKINNY) ||
		(instance->pdev->device == PCI_DEVICE_ID_LSI_SAS0071SKINNY) ||
		(instance->adapter_type != MFI_SERIES)) {
		if (!instance->requestorId) {
			writel(MFI_STOP_ADP, &instance->reg_set->doorbell);
			/* Flush */
			readl(&instance->reg_set->doorbell);
		}
		if (instance->requestorId && instance->peerIsPresent)
			memset(instance->ld_ids, 0xff, MEGASAS_MAX_LD_IDS);
	} else {
		writel(MFI_STOP_ADP,
			&instance->reg_set->inbound_doorbell);
	}
	/* Complete outstanding ioctls when adapter is killed */
	megasas_complete_outstanding_ioctls(instance);
}