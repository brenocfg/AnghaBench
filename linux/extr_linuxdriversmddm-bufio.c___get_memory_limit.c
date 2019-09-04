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
struct dm_bufio_client {unsigned long sectors_per_block_bits; unsigned long block_size; unsigned long minimum_buffers; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_BUFIO_WRITEBACK_PERCENT ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned long SECTOR_SHIFT ; 
 int /*<<< orphan*/  __cache_size_refresh () ; 
 int /*<<< orphan*/  dm_bufio_cache_size ; 
 scalar_t__ dm_bufio_cache_size_latch ; 
 unsigned long dm_bufio_cache_size_per_client ; 
 int /*<<< orphan*/  dm_bufio_clients_lock ; 
 scalar_t__ likely (int) ; 
 unsigned long mult_frac (unsigned long,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void __get_memory_limit(struct dm_bufio_client *c,
			       unsigned long *threshold_buffers,
			       unsigned long *limit_buffers)
{
	unsigned long buffers;

	if (unlikely(READ_ONCE(dm_bufio_cache_size) != dm_bufio_cache_size_latch)) {
		if (mutex_trylock(&dm_bufio_clients_lock)) {
			__cache_size_refresh();
			mutex_unlock(&dm_bufio_clients_lock);
		}
	}

	buffers = dm_bufio_cache_size_per_client;
	if (likely(c->sectors_per_block_bits >= 0))
		buffers >>= c->sectors_per_block_bits + SECTOR_SHIFT;
	else
		buffers /= c->block_size;

	if (buffers < c->minimum_buffers)
		buffers = c->minimum_buffers;

	*limit_buffers = buffers;
	*threshold_buffers = mult_frac(buffers,
				       DM_BUFIO_WRITEBACK_PERCENT, 100);
}