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
struct lpfc_hba {int /*<<< orphan*/  BIOSVersion; } ;
struct TYPE_2__ {int /*<<< orphan*/  AttrString; } ;
struct lpfc_fdmi_attr_entry {TYPE_1__ un; } ;
struct lpfc_fdmi_attr_def {void* AttrType; void* AttrLen; int /*<<< orphan*/  AttrValue; } ;

/* Variables and functions */
 int FOURBYTES ; 
 int RHBA_BIOS_VERSION ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  memset (struct lpfc_fdmi_attr_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int strnlen (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lpfc_fdmi_hba_attr_bios_ver(struct lpfc_vport *vport,
			    struct lpfc_fdmi_attr_def *ad)
{
	struct lpfc_hba *phba = vport->phba;
	struct lpfc_fdmi_attr_entry *ae;
	uint32_t len, size;

	ae = (struct lpfc_fdmi_attr_entry *)&ad->AttrValue;
	memset(ae, 0, 256);

	strlcat(ae->un.AttrString, phba->BIOSVersion,
		sizeof(ae->un.AttrString));
	len = strnlen(ae->un.AttrString,
			  sizeof(ae->un.AttrString));
	len += (len & 3) ? (4 - (len & 3)) : 4;
	size = FOURBYTES + len;
	ad->AttrLen = cpu_to_be16(size);
	ad->AttrType = cpu_to_be16(RHBA_BIOS_VERSION);
	return size;
}