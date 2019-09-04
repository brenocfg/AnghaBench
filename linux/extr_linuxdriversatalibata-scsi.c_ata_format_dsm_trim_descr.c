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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct scsi_device {size_t sector_size; } ;
struct scsi_cmnd {struct scsi_device* device; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 size_t ATA_SCSI_RBUF_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __cpu_to_le64 (int) ; 
 scalar_t__ ata_scsi_rbuf ; 
 int /*<<< orphan*/  ata_scsi_rbuf_lock ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  scsi_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sglist (struct scsi_cmnd*) ; 
 size_t sg_copy_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static size_t ata_format_dsm_trim_descr(struct scsi_cmnd *cmd, u32 trmax,
					u64 sector, u32 count)
{
	struct scsi_device *sdp = cmd->device;
	size_t len = sdp->sector_size;
	size_t r;
	__le64 *buf;
	u32 i = 0;
	unsigned long flags;

	WARN_ON(len > ATA_SCSI_RBUF_SIZE);

	if (len > ATA_SCSI_RBUF_SIZE)
		len = ATA_SCSI_RBUF_SIZE;

	spin_lock_irqsave(&ata_scsi_rbuf_lock, flags);
	buf = ((void *)ata_scsi_rbuf);
	memset(buf, 0, len);
	while (i < trmax) {
		u64 entry = sector |
			((u64)(count > 0xffff ? 0xffff : count) << 48);
		buf[i++] = __cpu_to_le64(entry);
		if (count <= 0xffff)
			break;
		count -= 0xffff;
		sector += 0xffff;
	}
	r = sg_copy_from_buffer(scsi_sglist(cmd), scsi_sg_count(cmd), buf, len);
	spin_unlock_irqrestore(&ata_scsi_rbuf_lock, flags);

	return r;
}