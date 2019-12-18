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
struct dm_bufio_client {int sectors_per_block_bits; int block_size; TYPE_1__* bdev; } ;
typedef  int sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  bd_inode; } ;

/* Variables and functions */
 int SECTOR_SHIFT ; 
 int i_size_read (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  sector_div (int,int) ; 

sector_t dm_bufio_get_device_size(struct dm_bufio_client *c)
{
	sector_t s = i_size_read(c->bdev->bd_inode) >> SECTOR_SHIFT;
	if (likely(c->sectors_per_block_bits >= 0))
		s >>= c->sectors_per_block_bits;
	else
		sector_div(s, c->block_size >> SECTOR_SHIFT);
	return s;
}