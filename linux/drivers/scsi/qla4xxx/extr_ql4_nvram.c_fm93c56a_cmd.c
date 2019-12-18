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
 int AUBURN_EEPROM_DO_0 ; 
 int AUBURN_EEPROM_DO_1 ; 
 int FM93C56A_CMD_BITS ; 
 int /*<<< orphan*/  eeprom_cmd (int,struct scsi_qla_host*) ; 
 int eeprom_no_addr_bits (struct scsi_qla_host*) ; 

__attribute__((used)) static int fm93c56a_cmd(struct scsi_qla_host * ha, int cmd, int addr)
{
	int i;
	int mask;
	int dataBit;
	int previousBit;

	/* Clock in a zero, then do the start bit. */
	eeprom_cmd(ha->eeprom_cmd_data | AUBURN_EEPROM_DO_1, ha);

	eeprom_cmd(ha->eeprom_cmd_data | AUBURN_EEPROM_DO_1 |
	       AUBURN_EEPROM_CLK_RISE, ha);
	eeprom_cmd(ha->eeprom_cmd_data | AUBURN_EEPROM_DO_1 |
	       AUBURN_EEPROM_CLK_FALL, ha);

	mask = 1 << (FM93C56A_CMD_BITS - 1);

	/* Force the previous data bit to be different. */
	previousBit = 0xffff;
	for (i = 0; i < FM93C56A_CMD_BITS; i++) {
		dataBit =
			(cmd & mask) ? AUBURN_EEPROM_DO_1 : AUBURN_EEPROM_DO_0;
		if (previousBit != dataBit) {

			/*
			 * If the bit changed, then change the DO state to
			 * match.
			 */
			eeprom_cmd(ha->eeprom_cmd_data | dataBit, ha);
			previousBit = dataBit;
		}
		eeprom_cmd(ha->eeprom_cmd_data | dataBit |
		       AUBURN_EEPROM_CLK_RISE, ha);
		eeprom_cmd(ha->eeprom_cmd_data | dataBit |
		       AUBURN_EEPROM_CLK_FALL, ha);

		cmd = cmd << 1;
	}
	mask = 1 << (eeprom_no_addr_bits(ha) - 1);

	/* Force the previous data bit to be different. */
	previousBit = 0xffff;
	for (i = 0; i < eeprom_no_addr_bits(ha); i++) {
		dataBit = addr & mask ? AUBURN_EEPROM_DO_1 :
			AUBURN_EEPROM_DO_0;
		if (previousBit != dataBit) {
			/*
			 * If the bit changed, then change the DO state to
			 * match.
			 */
			eeprom_cmd(ha->eeprom_cmd_data | dataBit, ha);

			previousBit = dataBit;
		}
		eeprom_cmd(ha->eeprom_cmd_data | dataBit |
		       AUBURN_EEPROM_CLK_RISE, ha);
		eeprom_cmd(ha->eeprom_cmd_data | dataBit |
		       AUBURN_EEPROM_CLK_FALL, ha);

		addr = addr << 1;
	}
	return 1;
}