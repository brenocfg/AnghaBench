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
struct scsi_qla_host {int eeprom_cmd_data; } ;

/* Variables and functions */
 int AUBURN_EEPROM_CLK_FALL ; 
 int AUBURN_EEPROM_CLK_RISE ; 
 int AUBURN_EEPROM_DI_1 ; 
 int /*<<< orphan*/  eeprom_cmd (int,struct scsi_qla_host*) ; 
 int eeprom_no_data_bits (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  isp_nvram (struct scsi_qla_host*) ; 
 int readw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fm93c56a_datain(struct scsi_qla_host * ha, unsigned short *value)
{
	int i;
	int data = 0;
	int dataBit;

	/* Read the data bits
	 * The first bit is a dummy.  Clock right over it. */
	for (i = 0; i < eeprom_no_data_bits(ha); i++) {
		eeprom_cmd(ha->eeprom_cmd_data |
		       AUBURN_EEPROM_CLK_RISE, ha);
		eeprom_cmd(ha->eeprom_cmd_data |
		       AUBURN_EEPROM_CLK_FALL, ha);

		dataBit = (readw(isp_nvram(ha)) & AUBURN_EEPROM_DI_1) ? 1 : 0;

		data = (data << 1) | dataBit;
	}

	*value = data;
	return 1;
}