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
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,unsigned long long) ; 
 int /*<<< orphan*/  b_sem ; 
 struct buf_cache_t* buf_cache_find (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (struct buf_cache_t*) ; 
 int /*<<< orphan*/  sector_write (struct super_block*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

void buf_modify(struct super_block *sb, sector_t sec)
{
	struct buf_cache_t *bp;

	down(&b_sem);

	bp = buf_cache_find(sb, sec);
	if (likely(bp))
		sector_write(sb, sec, bp->buf_bh, 0);

	WARN(!bp, "[EXFAT] failed to find buffer_cache(sector:%llu).\n",
	     (unsigned long long)sec);

	up(&b_sem);
}