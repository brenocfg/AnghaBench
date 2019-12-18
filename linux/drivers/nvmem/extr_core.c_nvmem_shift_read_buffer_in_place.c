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
struct nvmem_cell {int bit_offset; int bytes; int nbits; } ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 int DIV_ROUND_UP (int,int) ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvmem_shift_read_buffer_in_place(struct nvmem_cell *cell, void *buf)
{
	u8 *p, *b;
	int i, extra, bit_offset = cell->bit_offset;

	p = b = buf;
	if (bit_offset) {
		/* First shift */
		*b++ >>= bit_offset;

		/* setup rest of the bytes if any */
		for (i = 1; i < cell->bytes; i++) {
			/* Get bits from next byte and shift them towards msb */
			*p |= *b << (BITS_PER_BYTE - bit_offset);

			p = b;
			*b++ >>= bit_offset;
		}
	} else {
		/* point to the msb */
		p += cell->bytes - 1;
	}

	/* result fits in less bytes */
	extra = cell->bytes - DIV_ROUND_UP(cell->nbits, BITS_PER_BYTE);
	while (--extra >= 0)
		*p-- = 0;

	/* clear msb bits if any leftover in the last byte */
	*p &= GENMASK((cell->nbits%BITS_PER_BYTE) - 1, 0);
}