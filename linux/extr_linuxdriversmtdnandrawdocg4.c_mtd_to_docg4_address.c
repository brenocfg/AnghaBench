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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t mtd_to_docg4_address(int page, int column)
{
	/*
	 * Convert mtd address to format used by the device, 32 bit packed.
	 *
	 * Some notes on G4 addressing... The M-Sys documentation on this device
	 * claims that pages are 2K in length, and indeed, the format of the
	 * address used by the device reflects that.  But within each page are
	 * four 512 byte "sub-pages", each with its own oob data that is
	 * read/written immediately after the 512 bytes of page data.  This oob
	 * data contains the ecc bytes for the preceeding 512 bytes.
	 *
	 * Rather than tell the mtd nand infrastructure that page size is 2k,
	 * with four sub-pages each, we engage in a little subterfuge and tell
	 * the infrastructure code that pages are 512 bytes in size.  This is
	 * done because during the course of reverse-engineering the device, I
	 * never observed an instance where an entire 2K "page" was read or
	 * written as a unit.  Each "sub-page" is always addressed individually,
	 * its data read/written, and ecc handled before the next "sub-page" is
	 * addressed.
	 *
	 * This requires us to convert addresses passed by the mtd nand
	 * infrastructure code to those used by the device.
	 *
	 * The address that is written to the device consists of four bytes: the
	 * first two are the 2k page number, and the second is the index into
	 * the page.  The index is in terms of 16-bit half-words and includes
	 * the preceeding oob data, so e.g., the index into the second
	 * "sub-page" is 0x108, and the full device address of the start of mtd
	 * page 0x201 is 0x00800108.
	 */
	int g4_page = page / 4;	                      /* device's 2K page */
	int g4_index = (page % 4) * 0x108 + column/2; /* offset into page */
	return (g4_page << 16) | g4_index;	      /* pack */
}