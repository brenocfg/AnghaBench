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
struct super_block {int dummy; } ;
struct fs_info_t {int sectors_per_clu_bits; struct buf_cache_t* buf_cache_hash_list; } ;
struct buf_cache_t {int sec; struct buf_cache_t* hash_next; struct buf_cache_t* hash_prev; } ;
typedef  size_t s32 ;
struct TYPE_2__ {struct fs_info_t fs_info; } ;

/* Variables and functions */
 int BUF_CACHE_HASH_SIZE ; 
 TYPE_1__* EXFAT_SB (struct super_block*) ; 

__attribute__((used)) static void buf_cache_insert_hash(struct super_block *sb,
				  struct buf_cache_t *bp)
{
	s32 off;
	struct buf_cache_t *hp;
	struct fs_info_t *p_fs;

	p_fs = &(EXFAT_SB(sb)->fs_info);
	off = (bp->sec +
	       (bp->sec >> p_fs->sectors_per_clu_bits)) &
		(BUF_CACHE_HASH_SIZE - 1);

	hp = &p_fs->buf_cache_hash_list[off];
	bp->hash_next = hp->hash_next;
	bp->hash_prev = hp;
	hp->hash_next->hash_prev = bp;
	hp->hash_next = bp;
}