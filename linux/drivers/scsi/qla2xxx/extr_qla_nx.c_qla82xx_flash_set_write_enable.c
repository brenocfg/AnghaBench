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
typedef  int uint32_t ;
struct qla_hw_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M25P_INSTR_WREN ; 
 int /*<<< orphan*/  QLA82XX_ROMUSB_ROM_ABYTE_CNT ; 
 int /*<<< orphan*/  QLA82XX_ROMUSB_ROM_INSTR_OPCODE ; 
 scalar_t__ qla82xx_read_status_reg (struct qla_hw_data*,int*) ; 
 int /*<<< orphan*/  qla82xx_wait_rom_busy (struct qla_hw_data*) ; 
 scalar_t__ qla82xx_wait_rom_done (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla82xx_wr_32 (struct qla_hw_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla82xx_flash_set_write_enable(struct qla_hw_data *ha)
{
	uint32_t val;

	qla82xx_wait_rom_busy(ha);
	qla82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_ABYTE_CNT, 0);
	qla82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_INSTR_OPCODE, M25P_INSTR_WREN);
	qla82xx_wait_rom_busy(ha);
	if (qla82xx_wait_rom_done(ha))
		return -1;
	if (qla82xx_read_status_reg(ha, &val) != 0)
		return -1;
	if ((val & 2) != 2)
		return -1;
	return 0;
}