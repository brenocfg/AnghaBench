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
typedef  unsigned long long uint32_t ;

/* Variables and functions */
 int CP0_CERRD_DATA_DBE ; 
 int CP0_CERRD_DATA_SBE ; 
 int CP0_CERRD_TAG_ADDRESS ; 
 int CP0_CERRD_TAG_STATE ; 
 int DC_TAG_VALID (unsigned char) ; 
 int dc_ecc (unsigned long long) ; 
 int /*<<< orphan*/  dc_state_str (unsigned char) ; 
 int hweight8 (int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 unsigned long long range_parity (unsigned long long,int,int) ; 

__attribute__((used)) static uint32_t extract_dc(unsigned short addr, int data)
{
	int valid, way;
	unsigned char state;
	uint32_t taghi, taglolo, taglohi;
	unsigned long long taglo, pa;
	uint8_t ecc, lru;
	int res = 0;

	printk("Dcache index 0x%04x  ", addr);
	for (way = 0; way < 4; way++) {
		__asm__ __volatile__ (
		"	.set	push\n\t"
		"	.set	noreorder\n\t"
		"	.set	mips64\n\t"
		"	.set	noat\n\t"
		"	cache	5, 0(%3)\n\t"	/* Index-load-tag-D */
		"	mfc0	%0, $29, 2\n\t"
		"	dmfc0	$1, $28, 2\n\t"
		"	dsrl32	%1, $1, 0\n\t"
		"	sll	%2, $1, 0\n\t"
		"	.set	pop"
		: "=r" (taghi), "=r" (taglohi), "=r" (taglolo)
		: "r" ((way << 13) | addr));

		taglo = ((unsigned long long)taglohi << 32) | taglolo;
		pa = (taglo & 0xFFFFFFE000ULL) | addr;
		if (way == 0) {
			lru = (taghi >> 14) & 0xff;
			printk("[Bank %d Set 0x%02x]  LRU > %d %d %d %d > MRU\n",
				    ((addr >> 11) & 0x2) | ((addr >> 5) & 1), /* bank */
				    ((addr >> 6) & 0x3f), /* index */
				    (lru & 0x3),
				    ((lru >> 2) & 0x3),
				    ((lru >> 4) & 0x3),
				    ((lru >> 6) & 0x3));
		}
		state = (taghi >> 25) & 0x1f;
		valid = DC_TAG_VALID(state);
		printk(" %d  [PA %010llx]  [state %s (%02x)]  raw tags: %08X-%016llX\n",
			    way, pa, dc_state_str(state), state, taghi, taglo);
		if (valid) {
			if (((taglo >> 11) & 1) ^ range_parity(taglo, 39, 26)) {
				printk("   ** bad parity in PTag1\n");
				res |= CP0_CERRD_TAG_ADDRESS;
			}
			if (((taglo >> 10) & 1) ^ range_parity(taglo, 25, 13)) {
				printk("   ** bad parity in PTag0\n");
				res |= CP0_CERRD_TAG_ADDRESS;
			}
		} else {
			res |= CP0_CERRD_TAG_STATE;
		}

		if (data) {
			uint32_t datalohi, datalolo, datahi;
			unsigned long long datalo;
			int offset;
			char bad_ecc = 0;

			for (offset = 0; offset < 4; offset++) {
				/* Index-load-data-D */
				__asm__ __volatile__ (
				"	.set	push\n\t"
				"	.set	noreorder\n\t"
				"	.set	mips64\n\t"
				"	.set	noat\n\t"
				"	cache	7, 0(%3)\n\t" /* Index-load-data-D */
				"	mfc0	%0, $29, 3\n\t"
				"	dmfc0	$1, $28, 3\n\t"
				"	dsrl32	%1, $1, 0 \n\t"
				"	sll	%2, $1, 0 \n\t"
				"	.set	pop"
				: "=r" (datahi), "=r" (datalohi), "=r" (datalolo)
				: "r" ((way << 13) | addr | (offset << 3)));
				datalo = ((unsigned long long)datalohi << 32) | datalolo;
				ecc = dc_ecc(datalo);
				if (ecc != datahi) {
					int bits;
					bad_ecc |= 1 << (3-offset);
					ecc ^= datahi;
					bits = hweight8(ecc);
					res |= (bits == 1) ? CP0_CERRD_DATA_SBE : CP0_CERRD_DATA_DBE;
				}
				printk("  %02X-%016llX", datahi, datalo);
			}
			printk("\n");
			if (bad_ecc)
				printk("  dwords w/ bad ECC: %d %d %d %d\n",
				       !!(bad_ecc & 8), !!(bad_ecc & 4),
				       !!(bad_ecc & 2), !!(bad_ecc & 1));
		}
	}
	return res;
}