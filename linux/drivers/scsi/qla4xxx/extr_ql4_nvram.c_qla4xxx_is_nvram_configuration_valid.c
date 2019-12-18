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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct scsi_qla_host {int /*<<< orphan*/  hardware_lock; } ;

/* Variables and functions */
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 scalar_t__ eeprom_size (struct scsi_qla_host*) ; 
 scalar_t__ rd_nvram_word (struct scsi_qla_host*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int qla4xxx_is_nvram_configuration_valid(struct scsi_qla_host * ha)
{
	int status = QLA_ERROR;
	uint16_t checksum = 0;
	uint32_t index;
	unsigned long flags;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	for (index = 0; index < eeprom_size(ha); index++)
		checksum += rd_nvram_word(ha, index);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	if (checksum == 0)
		status = QLA_SUCCESS;

	return status;
}