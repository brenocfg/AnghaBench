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
struct scsi_qla_host {int /*<<< orphan*/  host; struct qla_hw_data* hw; } ;
struct qla_hw_data {int /*<<< orphan*/  mbx_cmd_flags; } ;

/* Variables and functions */
 scalar_t__ IS_QLA28XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  MBX_UPDATE_FLASH_ACTIVE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int qla24xx_write_flash_data (struct scsi_qla_host*,int*,int,int) ; 
 int qla28xx_write_flash_data (struct scsi_qla_host*,int*,int,int) ; 
 int /*<<< orphan*/  scsi_block_requests (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_unblock_requests (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
qla24xx_write_optrom_data(struct scsi_qla_host *vha, void *buf,
    uint32_t offset, uint32_t length)
{
	int rval;
	struct qla_hw_data *ha = vha->hw;

	/* Suspend HBA. */
	scsi_block_requests(vha->host);
	set_bit(MBX_UPDATE_FLASH_ACTIVE, &ha->mbx_cmd_flags);

	/* Go with write. */
	if (IS_QLA28XX(ha))
		rval = qla28xx_write_flash_data(vha, (uint32_t *)buf,
		    offset >> 2, length >> 2);
	else
		rval = qla24xx_write_flash_data(vha, (uint32_t *)buf,
		    offset >> 2, length >> 2);

	clear_bit(MBX_UPDATE_FLASH_ACTIVE, &ha->mbx_cmd_flags);
	scsi_unblock_requests(vha->host);

	return rval;
}