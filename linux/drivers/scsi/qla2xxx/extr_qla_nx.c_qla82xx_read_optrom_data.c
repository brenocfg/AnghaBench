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
typedef  int /*<<< orphan*/  uint32_t ;
struct scsi_qla_host {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  qla82xx_read_flash_data (struct scsi_qla_host*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_block_requests (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_unblock_requests (int /*<<< orphan*/ ) ; 

void *
qla82xx_read_optrom_data(struct scsi_qla_host *vha, void *buf,
	uint32_t offset, uint32_t length)
{
	scsi_block_requests(vha->host);
	qla82xx_read_flash_data(vha, (uint32_t *)buf, offset, length);
	scsi_unblock_requests(vha->host);
	return buf;
}