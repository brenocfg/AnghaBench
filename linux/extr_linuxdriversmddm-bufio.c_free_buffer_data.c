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
struct dm_bufio_client {scalar_t__ sectors_per_block_bits; int /*<<< orphan*/  slab_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  DATA_MODE_GET_FREE_PAGES 130 
#define  DATA_MODE_SLAB 129 
#define  DATA_MODE_VMALLOC 128 
 int /*<<< orphan*/  DMCRIT (char*,unsigned char) ; 
 scalar_t__ PAGE_SHIFT ; 
 scalar_t__ SECTOR_SHIFT ; 
 int /*<<< orphan*/  free_pages (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  vfree (void*) ; 

__attribute__((used)) static void free_buffer_data(struct dm_bufio_client *c,
			     void *data, unsigned char data_mode)
{
	switch (data_mode) {
	case DATA_MODE_SLAB:
		kmem_cache_free(c->slab_cache, data);
		break;

	case DATA_MODE_GET_FREE_PAGES:
		free_pages((unsigned long)data,
			   c->sectors_per_block_bits - (PAGE_SHIFT - SECTOR_SHIFT));
		break;

	case DATA_MODE_VMALLOC:
		vfree(data);
		break;

	default:
		DMCRIT("dm_bufio_free_buffer_data: bad data mode: %d",
		       data_mode);
		BUG();
	}
}