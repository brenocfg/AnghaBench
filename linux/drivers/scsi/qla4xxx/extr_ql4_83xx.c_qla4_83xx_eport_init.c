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
struct scsi_qla_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  QLA83XX_RESET_CONTROL ; 
 int /*<<< orphan*/  QLA83XX_RESET_EPG_SHIM ; 
 int /*<<< orphan*/  QLA83XX_RESET_ETHER_PCS ; 
 int /*<<< orphan*/  QLA83XX_RESET_PORT0 ; 
 int /*<<< orphan*/  QLA83XX_RESET_PORT1 ; 
 int /*<<< orphan*/  QLA83XX_RESET_PORT2 ; 
 int /*<<< orphan*/  QLA83XX_RESET_PORT3 ; 
 int /*<<< orphan*/  QLA83XX_RESET_REG ; 
 int /*<<< orphan*/  QLA83XX_RESET_SRE_SHIM ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*) ; 
 int /*<<< orphan*/  qla4_83xx_wr_reg_indirect (struct scsi_qla_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qla4_83xx_eport_init(struct scsi_qla_host *ha)
{
	/* Clear the 8 registers */
	qla4_83xx_wr_reg_indirect(ha, QLA83XX_RESET_REG, 0x0);
	qla4_83xx_wr_reg_indirect(ha, QLA83XX_RESET_PORT0, 0x0);
	qla4_83xx_wr_reg_indirect(ha, QLA83XX_RESET_PORT1, 0x0);
	qla4_83xx_wr_reg_indirect(ha, QLA83XX_RESET_PORT2, 0x0);
	qla4_83xx_wr_reg_indirect(ha, QLA83XX_RESET_PORT3, 0x0);
	qla4_83xx_wr_reg_indirect(ha, QLA83XX_RESET_SRE_SHIM, 0x0);
	qla4_83xx_wr_reg_indirect(ha, QLA83XX_RESET_EPG_SHIM, 0x0);
	qla4_83xx_wr_reg_indirect(ha, QLA83XX_RESET_ETHER_PCS, 0x0);

	/* Write any value to Reset Control register */
	qla4_83xx_wr_reg_indirect(ha, QLA83XX_RESET_CONTROL, 0xFF);

	ql4_printk(KERN_INFO, ha, "EPORT is out of reset.\n");
}