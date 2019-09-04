#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nftl_uci1 {int EraseMark; int EraseMark1; } ;
struct nftl_uci0 {int VirtUnitNum; int SpareVirtUnitNum; int ReplUnitNum; int SpareReplUnitNum; } ;
struct mtd_info {int dummy; } ;
struct TYPE_3__ {int FirstPhysicalEUN; } ;
struct TYPE_4__ {struct mtd_info* mtd; } ;
struct NFTLrecord {int nb_blocks; unsigned int* EUNtable; unsigned int* ReplUnitTable; unsigned int EraseSize; unsigned int LastFreeEUN; scalar_t__ numfreeEUNs; TYPE_1__ MediaHdr; TYPE_2__ mbd; } ;

/* Variables and functions */
 void* BLOCK_FREE ; 
 unsigned int BLOCK_NIL ; 
 unsigned int BLOCK_NOTEXPLORED ; 
 void* BLOCK_RESERVED ; 
 unsigned int ERASE_MARK ; 
 int FOLD_MARK_IN_PROGRESS ; 
 scalar_t__ NFTL_formatblock (struct NFTLrecord*,unsigned int) ; 
 unsigned int SECTORSIZE ; 
 unsigned int calc_chain_length (struct NFTLrecord*,unsigned int) ; 
 scalar_t__ check_and_mark_free_block (struct NFTLrecord*,unsigned int) ; 
 int /*<<< orphan*/  check_sectors_in_chain (struct NFTLrecord*,unsigned int) ; 
 scalar_t__ find_boot_record (struct NFTLrecord*) ; 
 int /*<<< orphan*/  format_chain (struct NFTLrecord*,unsigned int) ; 
 int get_fold_mark (struct NFTLrecord*,unsigned int) ; 
 void* le16_to_cpu (int) ; 
 scalar_t__ nftl_read_oob (struct mtd_info*,unsigned int,int,size_t*,char*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

int NFTL_mount(struct NFTLrecord *s)
{
	int i;
	unsigned int first_logical_block, logical_block, rep_block, erase_mark;
	unsigned int block, first_block, is_first_block;
	int chain_length, do_format_chain;
	struct nftl_uci0 h0;
	struct nftl_uci1 h1;
	struct mtd_info *mtd = s->mbd.mtd;
	size_t retlen;

	/* search for NFTL MediaHeader and Spare NFTL Media Header */
	if (find_boot_record(s) < 0) {
		printk("Could not find valid boot record\n");
		return -1;
	}

	/* init the logical to physical table */
	for (i = 0; i < s->nb_blocks; i++) {
		s->EUNtable[i] = BLOCK_NIL;
	}

	/* first pass : explore each block chain */
	first_logical_block = 0;
	for (first_block = 0; first_block < s->nb_blocks; first_block++) {
		/* if the block was not already explored, we can look at it */
		if (s->ReplUnitTable[first_block] == BLOCK_NOTEXPLORED) {
			block = first_block;
			chain_length = 0;
			do_format_chain = 0;

			for (;;) {
				/* read the block header. If error, we format the chain */
				if (nftl_read_oob(mtd,
						  block * s->EraseSize + 8, 8,
						  &retlen, (char *)&h0) < 0 ||
				    nftl_read_oob(mtd,
						  block * s->EraseSize +
						  SECTORSIZE + 8, 8,
						  &retlen, (char *)&h1) < 0) {
					s->ReplUnitTable[block] = BLOCK_NIL;
					do_format_chain = 1;
					break;
				}

				logical_block = le16_to_cpu ((h0.VirtUnitNum | h0.SpareVirtUnitNum));
				rep_block = le16_to_cpu ((h0.ReplUnitNum | h0.SpareReplUnitNum));
				erase_mark = le16_to_cpu ((h1.EraseMark | h1.EraseMark1));

				is_first_block = !(logical_block >> 15);
				logical_block = logical_block & 0x7fff;

				/* invalid/free block test */
				if (erase_mark != ERASE_MARK || logical_block >= s->nb_blocks) {
					if (chain_length == 0) {
						/* if not currently in a chain, we can handle it safely */
						if (check_and_mark_free_block(s, block) < 0) {
							/* not really free: format it */
							printk("Formatting block %d\n", block);
							if (NFTL_formatblock(s, block) < 0) {
								/* could not format: reserve the block */
								s->ReplUnitTable[block] = BLOCK_RESERVED;
							} else {
								s->ReplUnitTable[block] = BLOCK_FREE;
							}
						} else {
							/* free block: mark it */
							s->ReplUnitTable[block] = BLOCK_FREE;
						}
						/* directly examine the next block. */
						goto examine_ReplUnitTable;
					} else {
						/* the block was in a chain : this is bad. We
						   must format all the chain */
						printk("Block %d: free but referenced in chain %d\n",
						       block, first_block);
						s->ReplUnitTable[block] = BLOCK_NIL;
						do_format_chain = 1;
						break;
					}
				}

				/* we accept only first blocks here */
				if (chain_length == 0) {
					/* this block is not the first block in chain :
					   ignore it, it will be included in a chain
					   later, or marked as not explored */
					if (!is_first_block)
						goto examine_ReplUnitTable;
					first_logical_block = logical_block;
				} else {
					if (logical_block != first_logical_block) {
						printk("Block %d: incorrect logical block: %d expected: %d\n",
						       block, logical_block, first_logical_block);
						/* the chain is incorrect : we must format it,
						   but we need to read it completely */
						do_format_chain = 1;
					}
					if (is_first_block) {
						/* we accept that a block is marked as first
						   block while being last block in a chain
						   only if the chain is being folded */
						if (get_fold_mark(s, block) != FOLD_MARK_IN_PROGRESS ||
						    rep_block != 0xffff) {
							printk("Block %d: incorrectly marked as first block in chain\n",
							       block);
							/* the chain is incorrect : we must format it,
							   but we need to read it completely */
							do_format_chain = 1;
						} else {
							printk("Block %d: folding in progress - ignoring first block flag\n",
							       block);
						}
					}
				}
				chain_length++;
				if (rep_block == 0xffff) {
					/* no more blocks after */
					s->ReplUnitTable[block] = BLOCK_NIL;
					break;
				} else if (rep_block >= s->nb_blocks) {
					printk("Block %d: referencing invalid block %d\n",
					       block, rep_block);
					do_format_chain = 1;
					s->ReplUnitTable[block] = BLOCK_NIL;
					break;
				} else if (s->ReplUnitTable[rep_block] != BLOCK_NOTEXPLORED) {
					/* same problem as previous 'is_first_block' test:
					   we accept that the last block of a chain has
					   the first_block flag set if folding is in
					   progress. We handle here the case where the
					   last block appeared first */
					if (s->ReplUnitTable[rep_block] == BLOCK_NIL &&
					    s->EUNtable[first_logical_block] == rep_block &&
					    get_fold_mark(s, first_block) == FOLD_MARK_IN_PROGRESS) {
						/* EUNtable[] will be set after */
						printk("Block %d: folding in progress - ignoring first block flag\n",
						       rep_block);
						s->ReplUnitTable[block] = rep_block;
						s->EUNtable[first_logical_block] = BLOCK_NIL;
					} else {
						printk("Block %d: referencing block %d already in another chain\n",
						       block, rep_block);
						/* XXX: should handle correctly fold in progress chains */
						do_format_chain = 1;
						s->ReplUnitTable[block] = BLOCK_NIL;
					}
					break;
				} else {
					/* this is OK */
					s->ReplUnitTable[block] = rep_block;
					block = rep_block;
				}
			}

			/* the chain was completely explored. Now we can decide
			   what to do with it */
			if (do_format_chain) {
				/* invalid chain : format it */
				format_chain(s, first_block);
			} else {
				unsigned int first_block1, chain_to_format, chain_length1;
				int fold_mark;

				/* valid chain : get foldmark */
				fold_mark = get_fold_mark(s, first_block);
				if (fold_mark == 0) {
					/* cannot get foldmark : format the chain */
					printk("Could read foldmark at block %d\n", first_block);
					format_chain(s, first_block);
				} else {
					if (fold_mark == FOLD_MARK_IN_PROGRESS)
						check_sectors_in_chain(s, first_block);

					/* now handle the case where we find two chains at the
					   same virtual address : we select the longer one,
					   because the shorter one is the one which was being
					   folded if the folding was not done in place */
					first_block1 = s->EUNtable[first_logical_block];
					if (first_block1 != BLOCK_NIL) {
						/* XXX: what to do if same length ? */
						chain_length1 = calc_chain_length(s, first_block1);
						printk("Two chains at blocks %d (len=%d) and %d (len=%d)\n",
						       first_block1, chain_length1, first_block, chain_length);

						if (chain_length >= chain_length1) {
							chain_to_format = first_block1;
							s->EUNtable[first_logical_block] = first_block;
						} else {
							chain_to_format = first_block;
						}
						format_chain(s, chain_to_format);
					} else {
						s->EUNtable[first_logical_block] = first_block;
					}
				}
			}
		}
	examine_ReplUnitTable:;
	}

	/* second pass to format unreferenced blocks  and init free block count */
	s->numfreeEUNs = 0;
	s->LastFreeEUN = le16_to_cpu(s->MediaHdr.FirstPhysicalEUN);

	for (block = 0; block < s->nb_blocks; block++) {
		if (s->ReplUnitTable[block] == BLOCK_NOTEXPLORED) {
			printk("Unreferenced block %d, formatting it\n", block);
			if (NFTL_formatblock(s, block) < 0)
				s->ReplUnitTable[block] = BLOCK_RESERVED;
			else
				s->ReplUnitTable[block] = BLOCK_FREE;
		}
		if (s->ReplUnitTable[block] == BLOCK_FREE) {
			s->numfreeEUNs++;
			s->LastFreeEUN = block;
		}
	}

	return 0;
}