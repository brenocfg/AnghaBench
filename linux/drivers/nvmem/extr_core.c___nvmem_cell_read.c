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
struct nvmem_device {int dummy; } ;
struct nvmem_cell {size_t bytes; scalar_t__ nbits; scalar_t__ bit_offset; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int nvmem_reg_read (struct nvmem_device*,int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  nvmem_shift_read_buffer_in_place (struct nvmem_cell*,void*) ; 

__attribute__((used)) static int __nvmem_cell_read(struct nvmem_device *nvmem,
		      struct nvmem_cell *cell,
		      void *buf, size_t *len)
{
	int rc;

	rc = nvmem_reg_read(nvmem, cell->offset, buf, cell->bytes);

	if (rc)
		return rc;

	/* shift bits in-place */
	if (cell->bit_offset || cell->nbits)
		nvmem_shift_read_buffer_in_place(cell, buf);

	if (len)
		*len = cell->bytes;

	return 0;
}