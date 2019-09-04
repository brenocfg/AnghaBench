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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {struct mtd_info* mtd; } ;
struct ssfdcr_record {int map_len; unsigned long erase_size; int cis_block; unsigned short* logic_block_map; TYPE_1__ mbd; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int MAX_LOGIC_BLK_PER_ZONE ; 
 int MAX_PHYS_BLK_PER_ZONE ; 
 int OOB_SIZE ; 
 int get_logical_address (int /*<<< orphan*/ *) ; 
 scalar_t__ mtd_block_isbad (struct mtd_info*,unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int read_raw_oob (struct mtd_info*,unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int build_logical_block_map(struct ssfdcr_record *ssfdc)
{
	unsigned long offset;
	uint8_t oob_buf[OOB_SIZE];
	int ret, block_address, phys_block;
	struct mtd_info *mtd = ssfdc->mbd.mtd;

	pr_debug("SSFDC_RO: build_block_map() nblks=%d (%luK)\n",
	      ssfdc->map_len,
	      (unsigned long)ssfdc->map_len * ssfdc->erase_size / 1024);

	/* Scan every physical block, skip CIS block */
	for (phys_block = ssfdc->cis_block + 1; phys_block < ssfdc->map_len;
			phys_block++) {
		offset = (unsigned long)phys_block * ssfdc->erase_size;
		if (mtd_block_isbad(mtd, offset))
			continue;	/* skip bad blocks */

		ret = read_raw_oob(mtd, offset, oob_buf);
		if (ret < 0) {
			pr_debug("SSFDC_RO: mtd read_oob() failed at %lu\n",
				offset);
			return -1;
		}
		block_address = get_logical_address(oob_buf);

		/* Skip invalid addresses */
		if (block_address >= 0 &&
				block_address < MAX_LOGIC_BLK_PER_ZONE) {
			int zone_index;

			zone_index = phys_block / MAX_PHYS_BLK_PER_ZONE;
			block_address += zone_index * MAX_LOGIC_BLK_PER_ZONE;
			ssfdc->logic_block_map[block_address] =
				(unsigned short)phys_block;

			pr_debug("SSFDC_RO: build_block_map() phys_block=%d,"
				"logic_block_addr=%d, zone=%d\n",
				phys_block, block_address, zone_index);
		}
	}
	return 0;
}