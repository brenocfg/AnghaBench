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
struct dm_block {int dummy; } ;
struct disk_bitmap_header {int dummy; } ;

/* Variables and functions */
 void* dm_block_data (struct dm_block*) ; 

__attribute__((used)) static void *dm_bitmap_data(struct dm_block *b)
{
	return dm_block_data(b) + sizeof(struct disk_bitmap_header);
}