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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  unsigned long long uint32_t ;

/* Variables and functions */
 int CP0_CERRI_DATA_PARITY ; 
 int CP0_CERRI_TAG_PARITY ; 
 unsigned long long inst_parity (unsigned long long) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 unsigned long long range_parity (int,int,int) ; 

__attribute__((used)) static uint32_t extract_ic(unsigned short addr, int data)
{
	unsigned short way;
	int valid;
	uint32_t taghi, taglolo, taglohi;
	unsigned long long taglo, va;
	uint64_t tlo_tmp;
	uint8_t lru;
	int res = 0;

	printk("Icache index 0x%04x  ", addr);
	for (way = 0; way < 4; way++) {
		/* Index-load-tag-I */
		__asm__ __volatile__ (
		"	.set	push		\n\t"
		"	.set	noreorder	\n\t"
		"	.set	mips64		\n\t"
		"	.set	noat		\n\t"
		"	cache	4, 0(%3)	\n\t"
		"	mfc0	%0, $29		\n\t"
		"	dmfc0	$1, $28		\n\t"
		"	dsrl32	%1, $1, 0	\n\t"
		"	sll	%2, $1, 0	\n\t"
		"	.set	pop"
		: "=r" (taghi), "=r" (taglohi), "=r" (taglolo)
		: "r" ((way << 13) | addr));

		taglo = ((unsigned long long)taglohi << 32) | taglolo;
		if (way == 0) {
			lru = (taghi >> 14) & 0xff;
			printk("[Bank %d Set 0x%02x]  LRU > %d %d %d %d > MRU\n",
				    ((addr >> 5) & 0x3), /* bank */
				    ((addr >> 7) & 0x3f), /* index */
				    (lru & 0x3),
				    ((lru >> 2) & 0x3),
				    ((lru >> 4) & 0x3),
				    ((lru >> 6) & 0x3));
		}
		va = (taglo & 0xC0000FFFFFFFE000ULL) | addr;
		if ((taglo & (1 << 31)) && (((taglo >> 62) & 0x3) == 3))
			va |= 0x3FFFF00000000000ULL;
		valid = ((taghi >> 29) & 1);
		if (valid) {
			tlo_tmp = taglo & 0xfff3ff;
			if (((taglo >> 10) & 1) ^ range_parity(tlo_tmp, 23, 0)) {
				printk("   ** bad parity in VTag0/G/ASID\n");
				res |= CP0_CERRI_TAG_PARITY;
			}
			if (((taglo >> 11) & 1) ^ range_parity(taglo, 63, 24)) {
				printk("   ** bad parity in R/VTag1\n");
				res |= CP0_CERRI_TAG_PARITY;
			}
		}
		if (valid ^ ((taghi >> 27) & 1)) {
			printk("   ** bad parity for valid bit\n");
			res |= CP0_CERRI_TAG_PARITY;
		}
		printk(" %d  [VA %016llx]  [Vld? %d]  raw tags: %08X-%016llX\n",
			    way, va, valid, taghi, taglo);

		if (data) {
			uint32_t datahi, insta, instb;
			uint8_t predecode;
			int offset;

			/* (hit all banks and ways) */
			for (offset = 0; offset < 4; offset++) {
				/* Index-load-data-I */
				__asm__ __volatile__ (
				"	.set	push\n\t"
				"	.set	noreorder\n\t"
				"	.set	mips64\n\t"
				"	.set	noat\n\t"
				"	cache	6, 0(%3)  \n\t"
				"	mfc0	%0, $29, 1\n\t"
				"	dmfc0  $1, $28, 1\n\t"
				"	dsrl32 %1, $1, 0 \n\t"
				"	sll    %2, $1, 0 \n\t"
				"	.set	pop	    \n"
				: "=r" (datahi), "=r" (insta), "=r" (instb)
				: "r" ((way << 13) | addr | (offset << 3)));
				predecode = (datahi >> 8) & 0xff;
				if (((datahi >> 16) & 1) != (uint32_t)range_parity(predecode, 7, 0)) {
					printk("   ** bad parity in predecode\n");
					res |= CP0_CERRI_DATA_PARITY;
				}
				/* XXXKW should/could check predecode bits themselves */
				if (((datahi >> 4) & 0xf) ^ inst_parity(insta)) {
					printk("   ** bad parity in instruction a\n");
					res |= CP0_CERRI_DATA_PARITY;
				}
				if ((datahi & 0xf) ^ inst_parity(instb)) {
					printk("   ** bad parity in instruction b\n");
					res |= CP0_CERRI_DATA_PARITY;
				}
				printk("  %05X-%08X%08X", datahi, insta, instb);
			}
			printk("\n");
		}
	}
	return res;
}