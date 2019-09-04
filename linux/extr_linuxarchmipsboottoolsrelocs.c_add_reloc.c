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
struct relocs {int count; int size; int* offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 
 void* realloc (int*,unsigned long) ; 

__attribute__((used)) static void add_reloc(struct relocs *r, uint32_t offset, unsigned type)
{
	/* Relocation representation in binary table:
	 * |76543210|76543210|76543210|76543210|
	 * |  Type  |  offset from _text >> 2  |
	 */
	offset >>= 2;
	if (offset > 0x00FFFFFF)
		die("Kernel image exceeds maximum size for relocation!\n");

	offset = (offset & 0x00FFFFFF) | ((type & 0xFF) << 24);

	if (r->count == r->size) {
		unsigned long newsize = r->size + 50000;
		void *mem = realloc(r->offset, newsize * sizeof(r->offset[0]));

		if (!mem)
			die("realloc failed\n");

		r->offset = mem;
		r->size = newsize;
	}
	r->offset[r->count++] = offset;
}