#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct t10_pi_tuple {scalar_t__ app_tag; int /*<<< orphan*/  ref_tag; int /*<<< orphan*/  guard_tag; } ;
struct TYPE_2__ {unsigned int block_size; } ;
struct se_device {TYPE_1__ dev_attrib; } ;
struct se_cmd {scalar_t__ bad_sector; struct scatterlist* t_data_sg; struct se_device* se_dev; } ;
struct scatterlist {int offset; int length; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
typedef  scalar_t__ sector_t ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 scalar_t__ T10_PI_APP_ESCAPE ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crc_t10dif (void*,unsigned int) ; 
 int /*<<< orphan*/  crc_t10dif_update (int /*<<< orphan*/ ,void*,int) ; 
 void* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 unsigned int min (unsigned int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long long,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbc_dif_v1_verify (struct se_cmd*,struct t10_pi_tuple*,int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 

sense_reason_t
sbc_dif_verify(struct se_cmd *cmd, sector_t start, unsigned int sectors,
	       unsigned int ei_lba, struct scatterlist *psg, int psg_off)
{
	struct se_device *dev = cmd->se_dev;
	struct t10_pi_tuple *sdt;
	struct scatterlist *dsg = cmd->t_data_sg;
	sector_t sector = start;
	void *daddr, *paddr;
	int i;
	sense_reason_t rc;
	int dsg_off = 0;
	unsigned int block_size = dev->dev_attrib.block_size;

	for (; psg && sector < start + sectors; psg = sg_next(psg)) {
		paddr = kmap_atomic(sg_page(psg)) + psg->offset;
		daddr = kmap_atomic(sg_page(dsg)) + dsg->offset;

		for (i = psg_off; i < psg->length &&
				sector < start + sectors;
				i += sizeof(*sdt)) {
			__u16 crc;
			unsigned int avail;

			if (dsg_off >= dsg->length) {
				dsg_off -= dsg->length;
				kunmap_atomic(daddr - dsg->offset);
				dsg = sg_next(dsg);
				if (!dsg) {
					kunmap_atomic(paddr - psg->offset);
					return 0;
				}
				daddr = kmap_atomic(sg_page(dsg)) + dsg->offset;
			}

			sdt = paddr + i;

			pr_debug("DIF READ sector: %llu guard_tag: 0x%04x"
				 " app_tag: 0x%04x ref_tag: %u\n",
				 (unsigned long long)sector, sdt->guard_tag,
				 sdt->app_tag, be32_to_cpu(sdt->ref_tag));

			if (sdt->app_tag == T10_PI_APP_ESCAPE) {
				dsg_off += block_size;
				goto next;
			}

			avail = min(block_size, dsg->length - dsg_off);
			crc = crc_t10dif(daddr + dsg_off, avail);
			if (avail < block_size) {
				kunmap_atomic(daddr - dsg->offset);
				dsg = sg_next(dsg);
				if (!dsg) {
					kunmap_atomic(paddr - psg->offset);
					return 0;
				}
				daddr = kmap_atomic(sg_page(dsg)) + dsg->offset;
				dsg_off = block_size - avail;
				crc = crc_t10dif_update(crc, daddr, dsg_off);
			} else {
				dsg_off += block_size;
			}

			rc = sbc_dif_v1_verify(cmd, sdt, crc, sector, ei_lba);
			if (rc) {
				kunmap_atomic(daddr - dsg->offset);
				kunmap_atomic(paddr - psg->offset);
				cmd->bad_sector = sector;
				return rc;
			}
next:
			sector++;
			ei_lba++;
		}

		psg_off = 0;
		kunmap_atomic(daddr - dsg->offset);
		kunmap_atomic(paddr - psg->offset);
	}

	return 0;
}