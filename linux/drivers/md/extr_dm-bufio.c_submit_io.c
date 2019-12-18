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
struct dm_buffer {void (* end_io ) (struct dm_buffer*,blk_status_t) ;unsigned int block; unsigned int write_start; unsigned int write_end; scalar_t__ data_mode; TYPE_1__* c; } ;
typedef  unsigned int sector_t ;
struct TYPE_2__ {unsigned int sectors_per_block_bits; unsigned int block_size; int /*<<< orphan*/  (* write_callback ) (struct dm_buffer*) ;scalar_t__ start; } ;

/* Variables and functions */
 scalar_t__ DATA_MODE_VMALLOC ; 
 unsigned int DM_BUFIO_WRITE_ALIGN ; 
 int REQ_OP_WRITE ; 
 unsigned int SECTOR_SHIFT ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  stub1 (struct dm_buffer*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  use_bio (struct dm_buffer*,int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  use_dmio (struct dm_buffer*,int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void submit_io(struct dm_buffer *b, int rw, void (*end_io)(struct dm_buffer *, blk_status_t))
{
	unsigned n_sectors;
	sector_t sector;
	unsigned offset, end;

	b->end_io = end_io;

	if (likely(b->c->sectors_per_block_bits >= 0))
		sector = b->block << b->c->sectors_per_block_bits;
	else
		sector = b->block * (b->c->block_size >> SECTOR_SHIFT);
	sector += b->c->start;

	if (rw != REQ_OP_WRITE) {
		n_sectors = b->c->block_size >> SECTOR_SHIFT;
		offset = 0;
	} else {
		if (b->c->write_callback)
			b->c->write_callback(b);
		offset = b->write_start;
		end = b->write_end;
		offset &= -DM_BUFIO_WRITE_ALIGN;
		end += DM_BUFIO_WRITE_ALIGN - 1;
		end &= -DM_BUFIO_WRITE_ALIGN;
		if (unlikely(end > b->c->block_size))
			end = b->c->block_size;

		sector += offset >> SECTOR_SHIFT;
		n_sectors = (end - offset) >> SECTOR_SHIFT;
	}

	if (b->data_mode != DATA_MODE_VMALLOC)
		use_bio(b, rw, sector, n_sectors, offset);
	else
		use_dmio(b, rw, sector, n_sectors, offset);
}