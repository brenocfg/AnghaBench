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
typedef  int u32 ;
struct sas_ha_struct {struct pm8001_hba_info* lldd_ha; } ;
struct pm8001_hba_info {int fatal_forensic_shift_offset; scalar_t__ chip_id; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int GSM_BASE ; 
 int SHIFT_REG_64K_MASK ; 
 int SHIFT_REG_BIT_SHIFT ; 
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 scalar_t__ chip_8001 ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int pm8001_bar4_shift (struct pm8001_hba_info*,int) ; 
 int pm8001_cr32 (struct pm8001_hba_info*,int,int) ; 
 int pm80xx_bar4_shift (struct pm8001_hba_info*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

ssize_t
pm8001_get_gsm_dump(struct device *cdev, u32 length, char *buf)
{
	u32 value, rem, offset = 0, bar = 0;
	u32 index, work_offset, dw_length;
	u32 shift_value, gsm_base, gsm_dump_offset;
	char *direct_data;
	struct Scsi_Host *shost = class_to_shost(cdev);
	struct sas_ha_struct *sha = SHOST_TO_SAS_HA(shost);
	struct pm8001_hba_info *pm8001_ha = sha->lldd_ha;

	direct_data = buf;
	gsm_dump_offset = pm8001_ha->fatal_forensic_shift_offset;

	/* check max is 1 Mbytes */
	if ((length > 0x100000) || (gsm_dump_offset & 3) ||
		((gsm_dump_offset + length) > 0x1000000))
			return -EINVAL;

	if (pm8001_ha->chip_id == chip_8001)
		bar = 2;
	else
		bar = 1;

	work_offset = gsm_dump_offset & 0xFFFF0000;
	offset = gsm_dump_offset & 0x0000FFFF;
	gsm_dump_offset = work_offset;
	/* adjust length to dword boundary */
	rem = length & 3;
	dw_length = length >> 2;

	for (index = 0; index < dw_length; index++) {
		if ((work_offset + offset) & 0xFFFF0000) {
			if (pm8001_ha->chip_id == chip_8001)
				shift_value = ((gsm_dump_offset + offset) &
						SHIFT_REG_64K_MASK);
			else
				shift_value = (((gsm_dump_offset + offset) &
						SHIFT_REG_64K_MASK) >>
						SHIFT_REG_BIT_SHIFT);

			if (pm8001_ha->chip_id == chip_8001) {
				gsm_base = GSM_BASE;
				if (-1 == pm8001_bar4_shift(pm8001_ha,
						(gsm_base + shift_value)))
					return -EIO;
			} else {
				gsm_base = 0;
				if (-1 == pm80xx_bar4_shift(pm8001_ha,
						(gsm_base + shift_value)))
					return -EIO;
			}
			gsm_dump_offset = (gsm_dump_offset + offset) &
						0xFFFF0000;
			work_offset = 0;
			offset = offset & 0x0000FFFF;
		}
		value = pm8001_cr32(pm8001_ha, bar, (work_offset + offset) &
						0x0000FFFF);
		direct_data += sprintf(direct_data, "%08x ", value);
		offset += 4;
	}
	if (rem != 0) {
		value = pm8001_cr32(pm8001_ha, bar, (work_offset + offset) &
						0x0000FFFF);
		/* xfr for non_dw */
		direct_data += sprintf(direct_data, "%08x ", value);
	}
	/* Shift back to BAR4 original address */
	if (-1 == pm8001_bar4_shift(pm8001_ha, 0))
			return -EIO;
	pm8001_ha->fatal_forensic_shift_offset += 1024;

	if (pm8001_ha->fatal_forensic_shift_offset >= 0x100000)
		pm8001_ha->fatal_forensic_shift_offset = 0;
	return direct_data - buf;
}