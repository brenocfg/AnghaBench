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
typedef  int uint32_t ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct TYPE_4__ {scalar_t__ nvme; } ;
struct TYPE_5__ {TYPE_1__ pc_sli4_params; } ;
struct lpfc_hba {scalar_t__ sli_rev; TYPE_2__ sli4_hba; struct lpfc_vport* pport; } ;
struct TYPE_6__ {int* AttrTypes; } ;
struct lpfc_fdmi_attr_entry {TYPE_3__ un; } ;
struct lpfc_fdmi_attr_def {void* AttrType; void* AttrLen; int /*<<< orphan*/  AttrValue; } ;

/* Variables and functions */
 int FOURBYTES ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int RPRT_SUPPORTED_FC4_TYPES ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  memset (struct lpfc_fdmi_attr_entry*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lpfc_fdmi_port_attr_fc4type(struct lpfc_vport *vport,
			    struct lpfc_fdmi_attr_def *ad)
{
	struct lpfc_hba   *phba = vport->phba;
	struct lpfc_fdmi_attr_entry *ae;
	uint32_t size;

	ae = (struct lpfc_fdmi_attr_entry *)&ad->AttrValue;
	memset(ae, 0, 32);

	ae->un.AttrTypes[3] = 0x02; /* Type 0x1 - ELS */
	ae->un.AttrTypes[2] = 0x01; /* Type 0x8 - FCP */
	ae->un.AttrTypes[7] = 0x01; /* Type 0x20 - CT */

	/* Check to see if Firmware supports NVME and on physical port */
	if ((phba->sli_rev == LPFC_SLI_REV4) && (vport == phba->pport) &&
	    phba->sli4_hba.pc_sli4_params.nvme)
		ae->un.AttrTypes[6] = 0x01; /* Type 0x28 - NVME */

	size = FOURBYTES + 32;
	ad->AttrLen = cpu_to_be16(size);
	ad->AttrType = cpu_to_be16(RPRT_SUPPORTED_FC4_TYPES);
	return size;
}