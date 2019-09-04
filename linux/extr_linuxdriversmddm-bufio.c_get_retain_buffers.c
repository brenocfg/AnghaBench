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
struct dm_bufio_client {unsigned long sectors_per_block_bits; unsigned long block_size; } ;

/* Variables and functions */
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned long SECTOR_SHIFT ; 
 int /*<<< orphan*/  dm_bufio_retain_bytes ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static unsigned long get_retain_buffers(struct dm_bufio_client *c)
{
	unsigned long retain_bytes = READ_ONCE(dm_bufio_retain_bytes);
	if (likely(c->sectors_per_block_bits >= 0))
		retain_bytes >>= c->sectors_per_block_bits + SECTOR_SHIFT;
	else
		retain_bytes /= c->block_size;
	return retain_bytes;
}