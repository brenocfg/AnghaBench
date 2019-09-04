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
struct bch_geometry {unsigned int block_mark_bit_offset; int block_mark_byte_offset; } ;
struct gpmi_nand_data {int /*<<< orphan*/  swap_block_mark; struct bch_geometry bch_geometry; } ;

/* Variables and functions */

__attribute__((used)) static void block_mark_swapping(struct gpmi_nand_data *this,
				void *payload, void *auxiliary)
{
	struct bch_geometry *nfc_geo = &this->bch_geometry;
	unsigned char *p;
	unsigned char *a;
	unsigned int  bit;
	unsigned char mask;
	unsigned char from_data;
	unsigned char from_oob;

	if (!this->swap_block_mark)
		return;

	/*
	 * If control arrives here, we're swapping. Make some convenience
	 * variables.
	 */
	bit = nfc_geo->block_mark_bit_offset;
	p   = payload + nfc_geo->block_mark_byte_offset;
	a   = auxiliary;

	/*
	 * Get the byte from the data area that overlays the block mark. Since
	 * the ECC engine applies its own view to the bits in the page, the
	 * physical block mark won't (in general) appear on a byte boundary in
	 * the data.
	 */
	from_data = (p[0] >> bit) | (p[1] << (8 - bit));

	/* Get the byte from the OOB. */
	from_oob = a[0];

	/* Swap them. */
	a[0] = from_data;

	mask = (0x1 << bit) - 1;
	p[0] = (p[0] & mask) | (from_oob << bit);

	mask = ~0 << bit;
	p[1] = (p[1] & mask) | (from_oob >> (8 - bit));
}