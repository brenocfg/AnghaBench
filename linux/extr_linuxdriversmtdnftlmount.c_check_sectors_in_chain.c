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
struct nftl_bci {unsigned int Status; unsigned int Status1; } ;
struct mtd_info {int dummy; } ;
struct TYPE_2__ {struct mtd_info* mtd; } ;
struct NFTLrecord {unsigned int EraseSize; unsigned int* ReplUnitTable; unsigned int nb_blocks; TYPE_1__ mbd; } ;

/* Variables and functions */
 unsigned int BLOCK_NIL ; 
 unsigned int SECTORSIZE ; 
#define  SECTOR_FREE 128 
 void* SECTOR_IGNORE ; 
 int /*<<< orphan*/  check_free_sectors (struct NFTLrecord*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmpb (struct nftl_bci*,int,int) ; 
 scalar_t__ nftl_read_oob (struct mtd_info*,unsigned int,int,size_t*,char*) ; 
 int /*<<< orphan*/  nftl_write_oob (struct mtd_info*,unsigned int,int,size_t*,char*) ; 
 int /*<<< orphan*/  printk (char*,unsigned int,...) ; 

__attribute__((used)) static void check_sectors_in_chain(struct NFTLrecord *nftl, unsigned int first_block)
{
	struct mtd_info *mtd = nftl->mbd.mtd;
	unsigned int block, i, status;
	struct nftl_bci bci;
	int sectors_per_block;
	size_t retlen;

	sectors_per_block = nftl->EraseSize / SECTORSIZE;
	block = first_block;
	for (;;) {
		for (i = 0; i < sectors_per_block; i++) {
			if (nftl_read_oob(mtd,
					  block * nftl->EraseSize + i * SECTORSIZE,
					  8, &retlen, (char *)&bci) < 0)
				status = SECTOR_IGNORE;
			else
				status = bci.Status | bci.Status1;

			switch(status) {
			case SECTOR_FREE:
				/* verify that the sector is really free. If not, mark
				   as ignore */
				if (memcmpb(&bci, 0xff, 8) != 0 ||
				    check_free_sectors(nftl, block * nftl->EraseSize + i * SECTORSIZE,
						       SECTORSIZE, 0) != 0) {
					printk("Incorrect free sector %d in block %d: "
					       "marking it as ignored\n",
					       i, block);

					/* sector not free actually : mark it as SECTOR_IGNORE  */
					bci.Status = SECTOR_IGNORE;
					bci.Status1 = SECTOR_IGNORE;
					nftl_write_oob(mtd, block *
						       nftl->EraseSize +
						       i * SECTORSIZE, 8,
						       &retlen, (char *)&bci);
				}
				break;
			default:
				break;
			}
		}

		/* proceed to next Erase Unit on the chain */
		block = nftl->ReplUnitTable[block];
		if (!(block == BLOCK_NIL || block < nftl->nb_blocks))
			printk("incorrect ReplUnitTable[] : %d\n", block);
		if (block == BLOCK_NIL || block >= nftl->nb_blocks)
			break;
	}
}