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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct sg_mapping_iter {char* addr; unsigned int length; } ;
struct scsi_cmnd {int dummy; } ;
struct ata_queued_cmd {struct scsi_cmnd* scsicmd; } ;

/* Variables and functions */
 int SG_MITER_ATOMIC ; 
 int SG_MITER_TO_SG ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ata_scsi_qc_complete (struct ata_queued_cmd*) ; 
 int get_unaligned_le16 (char*) ; 
 int /*<<< orphan*/  get_unaligned_le32 (char*) ; 
 int /*<<< orphan*/  get_unaligned_le64 (char*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  put_unaligned_be64 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  scsi_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sglist (struct scsi_cmnd*) ; 
 scalar_t__ sg_miter_next (struct sg_mapping_iter*) ; 
 int /*<<< orphan*/  sg_miter_start (struct sg_mapping_iter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_miter_stop (struct sg_mapping_iter*) ; 

__attribute__((used)) static void ata_scsi_report_zones_complete(struct ata_queued_cmd *qc)
{
	struct scsi_cmnd *scmd = qc->scsicmd;
	struct sg_mapping_iter miter;
	unsigned long flags;
	unsigned int bytes = 0;

	sg_miter_start(&miter, scsi_sglist(scmd), scsi_sg_count(scmd),
		       SG_MITER_TO_SG | SG_MITER_ATOMIC);

	local_irq_save(flags);
	while (sg_miter_next(&miter)) {
		unsigned int offset = 0;

		if (bytes == 0) {
			char *hdr;
			u32 list_length;
			u64 max_lba, opt_lba;
			u16 same;

			/* Swizzle header */
			hdr = miter.addr;
			list_length = get_unaligned_le32(&hdr[0]);
			same = get_unaligned_le16(&hdr[4]);
			max_lba = get_unaligned_le64(&hdr[8]);
			opt_lba = get_unaligned_le64(&hdr[16]);
			put_unaligned_be32(list_length, &hdr[0]);
			hdr[4] = same & 0xf;
			put_unaligned_be64(max_lba, &hdr[8]);
			put_unaligned_be64(opt_lba, &hdr[16]);
			offset += 64;
			bytes += 64;
		}
		while (offset < miter.length) {
			char *rec;
			u8 cond, type, non_seq, reset;
			u64 size, start, wp;

			/* Swizzle zone descriptor */
			rec = miter.addr + offset;
			type = rec[0] & 0xf;
			cond = (rec[1] >> 4) & 0xf;
			non_seq = (rec[1] & 2);
			reset = (rec[1] & 1);
			size = get_unaligned_le64(&rec[8]);
			start = get_unaligned_le64(&rec[16]);
			wp = get_unaligned_le64(&rec[24]);
			rec[0] = type;
			rec[1] = (cond << 4) | non_seq | reset;
			put_unaligned_be64(size, &rec[8]);
			put_unaligned_be64(start, &rec[16]);
			put_unaligned_be64(wp, &rec[24]);
			WARN_ON(offset + 64 > miter.length);
			offset += 64;
			bytes += 64;
		}
	}
	sg_miter_stop(&miter);
	local_irq_restore(flags);

	ata_scsi_qc_complete(qc);
}