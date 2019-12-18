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
typedef  scalar_t__ uint8_t ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_hba {scalar_t__ cfg_XLanePriority; scalar_t__ cfg_oas_priority; int /*<<< orphan*/  cfg_fof; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t EPERM ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static ssize_t
lpfc_oas_priority_store(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct lpfc_hba *phba = ((struct lpfc_vport *)shost->hostdata)->phba;
	unsigned int cnt = count;
	unsigned long val;
	int ret;

	if (!phba->cfg_fof)
		return -EPERM;

	/* count may include a LF at end of string */
	if (buf[cnt-1] == '\n')
		cnt--;

	ret = kstrtoul(buf, 0, &val);
	if (ret || (val > 0x7f))
		return -EINVAL;

	if (val)
		phba->cfg_oas_priority = (uint8_t)val;
	else
		phba->cfg_oas_priority = phba->cfg_XLanePriority;
	return count;
}