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
typedef  int uint32_t ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_hba {scalar_t__ sli_rev; int /*<<< orphan*/  OptionROMVersion; } ;
struct TYPE_2__ {int /*<<< orphan*/  AttrString; } ;
struct lpfc_fdmi_attr_entry {TYPE_1__ un; } ;
struct lpfc_fdmi_attr_def {void* AttrType; void* AttrLen; int /*<<< orphan*/  AttrValue; } ;

/* Variables and functions */
 int FOURBYTES ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int RHBA_OPTION_ROM_VERSION ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  lpfc_decode_firmware_rev (struct lpfc_hba*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct lpfc_fdmi_attr_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int strnlen (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lpfc_fdmi_hba_attr_rom_ver(struct lpfc_vport *vport,
			   struct lpfc_fdmi_attr_def *ad)
{
	struct lpfc_hba *phba = vport->phba;
	struct lpfc_fdmi_attr_entry *ae;
	uint32_t len, size;

	ae = (struct lpfc_fdmi_attr_entry *)&ad->AttrValue;
	memset(ae, 0, 256);

	if (phba->sli_rev == LPFC_SLI_REV4)
		lpfc_decode_firmware_rev(phba, ae->un.AttrString, 1);
	else
		strncpy(ae->un.AttrString, phba->OptionROMVersion,
			sizeof(ae->un.AttrString));
	len = strnlen(ae->un.AttrString,
			  sizeof(ae->un.AttrString));
	len += (len & 3) ? (4 - (len & 3)) : 4;
	size = FOURBYTES + len;
	ad->AttrLen = cpu_to_be16(size);
	ad->AttrType = cpu_to_be16(RHBA_OPTION_ROM_VERSION);
	return size;
}