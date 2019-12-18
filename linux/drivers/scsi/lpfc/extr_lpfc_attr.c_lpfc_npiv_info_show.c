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
struct lpfc_vport {scalar_t__ port_type; int /*<<< orphan*/  vpi; struct lpfc_hba* phba; } ;
struct lpfc_hba {int /*<<< orphan*/  max_vpi; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ LPFC_PHYSICAL_PORT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static ssize_t
lpfc_npiv_info_show(struct device *dev, struct device_attribute *attr,
		    char *buf)
{
	struct Scsi_Host  *shost = class_to_shost(dev);
	struct lpfc_vport *vport = (struct lpfc_vport *) shost->hostdata;
	struct lpfc_hba   *phba = vport->phba;

	if (!(phba->max_vpi))
		return scnprintf(buf, PAGE_SIZE, "NPIV Not Supported\n");
	if (vport->port_type == LPFC_PHYSICAL_PORT)
		return scnprintf(buf, PAGE_SIZE, "NPIV Physical\n");
	return scnprintf(buf, PAGE_SIZE, "NPIV Virtual (VPI %d)\n", vport->vpi);
}