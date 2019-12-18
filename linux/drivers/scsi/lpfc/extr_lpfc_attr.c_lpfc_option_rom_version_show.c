#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_hba {scalar_t__ sli_rev; char* OptionROMVersion; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int FW_REV_STR_SIZE ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  lpfc_decode_firmware_rev (struct lpfc_hba*,char*,int) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static ssize_t
lpfc_option_rom_version_show(struct device *dev, struct device_attribute *attr,
			     char *buf)
{
	struct Scsi_Host  *shost = class_to_shost(dev);
	struct lpfc_vport *vport = (struct lpfc_vport *) shost->hostdata;
	struct lpfc_hba   *phba = vport->phba;
	char fwrev[FW_REV_STR_SIZE];

	if (phba->sli_rev < LPFC_SLI_REV4)
		return scnprintf(buf, PAGE_SIZE, "%s\n",
				phba->OptionROMVersion);

	lpfc_decode_firmware_rev(phba, fwrev, 1);
	return scnprintf(buf, PAGE_SIZE, "%s\n", fwrev);
}