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
typedef  int /*<<< orphan*/  u32 ;
struct t10_pi_tuple {int dummy; } ;
struct sg_mapping_iter {int length; int consumed; struct t10_pi_tuple* addr; } ;
struct scsi_cmnd {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int SG_MITER_ATOMIC ; 
 int SG_MITER_FROM_SG ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dif_copy_prot (struct scsi_cmnd*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  dif_errors ; 
 int dif_verify (struct t10_pi_tuple*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dix_writes ; 
 int /*<<< orphan*/  dump_sector (void*,scalar_t__) ; 
 scalar_t__ scsi_prot_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_prot_sglist (struct scsi_cmnd*) ; 
 scalar_t__ scsi_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sglist (struct scsi_cmnd*) ; 
 scalar_t__ sdebug_sector_size ; 
 scalar_t__ sg_miter_next (struct sg_mapping_iter*) ; 
 int /*<<< orphan*/  sg_miter_start (struct sg_mapping_iter*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  sg_miter_stop (struct sg_mapping_iter*) ; 

__attribute__((used)) static int prot_verify_write(struct scsi_cmnd *SCpnt, sector_t start_sec,
			     unsigned int sectors, u32 ei_lba)
{
	int ret;
	struct t10_pi_tuple *sdt;
	void *daddr;
	sector_t sector = start_sec;
	int ppage_offset;
	int dpage_offset;
	struct sg_mapping_iter diter;
	struct sg_mapping_iter piter;

	BUG_ON(scsi_sg_count(SCpnt) == 0);
	BUG_ON(scsi_prot_sg_count(SCpnt) == 0);

	sg_miter_start(&piter, scsi_prot_sglist(SCpnt),
			scsi_prot_sg_count(SCpnt),
			SG_MITER_ATOMIC | SG_MITER_FROM_SG);
	sg_miter_start(&diter, scsi_sglist(SCpnt), scsi_sg_count(SCpnt),
			SG_MITER_ATOMIC | SG_MITER_FROM_SG);

	/* For each protection page */
	while (sg_miter_next(&piter)) {
		dpage_offset = 0;
		if (WARN_ON(!sg_miter_next(&diter))) {
			ret = 0x01;
			goto out;
		}

		for (ppage_offset = 0; ppage_offset < piter.length;
		     ppage_offset += sizeof(struct t10_pi_tuple)) {
			/* If we're at the end of the current
			 * data page advance to the next one
			 */
			if (dpage_offset >= diter.length) {
				if (WARN_ON(!sg_miter_next(&diter))) {
					ret = 0x01;
					goto out;
				}
				dpage_offset = 0;
			}

			sdt = piter.addr + ppage_offset;
			daddr = diter.addr + dpage_offset;

			ret = dif_verify(sdt, daddr, sector, ei_lba);
			if (ret) {
				dump_sector(daddr, sdebug_sector_size);
				goto out;
			}

			sector++;
			ei_lba++;
			dpage_offset += sdebug_sector_size;
		}
		diter.consumed = dpage_offset;
		sg_miter_stop(&diter);
	}
	sg_miter_stop(&piter);

	dif_copy_prot(SCpnt, start_sec, sectors, false);
	dix_writes++;

	return 0;

out:
	dif_errors++;
	sg_miter_stop(&diter);
	sg_miter_stop(&piter);
	return ret;
}