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
 int /*<<< orphan*/  QLA83XX_FLASH_LOCK_ID ; 
 int /*<<< orphan*/  QLA83XX_FLASH_UNLOCK ; 
 int /*<<< orphan*/  qla4_83xx_rd_reg (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla4_83xx_wr_reg (struct scsi_qla_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qla4_83xx_flash_unlock(struct scsi_qla_host *ha)
{
	/* Reading FLASH_UNLOCK register unlocks the Flash */
	qla4_83xx_wr_reg(ha, QLA83XX_FLASH_LOCK_ID, 0xFF);
	qla4_83xx_rd_reg(ha, QLA83XX_FLASH_UNLOCK);
}