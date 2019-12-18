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
struct super_block {int dummy; } ;
struct buf_cache_t {int /*<<< orphan*/  buf_bh; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 struct buf_cache_t* FAT_cache_find (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sector_write (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void FAT_modify(struct super_block *sb, sector_t sec)
{
	struct buf_cache_t *bp;

	bp = FAT_cache_find(sb, sec);
	if (bp)
		sector_write(sb, sec, bp->buf_bh, 0);
}