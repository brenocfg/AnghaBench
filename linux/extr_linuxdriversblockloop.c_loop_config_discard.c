#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ discard_alignment; scalar_t__ discard_granularity; } ;
struct request_queue {TYPE_4__ limits; } ;
struct loop_device {scalar_t__ lo_encrypt_key_size; struct request_queue* lo_queue; struct file* lo_backing_file; } ;
struct inode {TYPE_3__* i_sb; } ;
struct file {TYPE_2__* f_op; TYPE_1__* f_mapping; } ;
struct TYPE_7__ {scalar_t__ s_blocksize; } ;
struct TYPE_6__ {int /*<<< orphan*/  fallocate; } ;
struct TYPE_5__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_DISCARD ; 
 int UINT_MAX ; 
 int /*<<< orphan*/  blk_queue_flag_clear (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_max_discard_sectors (struct request_queue*,int) ; 
 int /*<<< orphan*/  blk_queue_max_write_zeroes_sectors (struct request_queue*,int) ; 

__attribute__((used)) static void loop_config_discard(struct loop_device *lo)
{
	struct file *file = lo->lo_backing_file;
	struct inode *inode = file->f_mapping->host;
	struct request_queue *q = lo->lo_queue;

	/*
	 * We use punch hole to reclaim the free space used by the
	 * image a.k.a. discard. However we do not support discard if
	 * encryption is enabled, because it may give an attacker
	 * useful information.
	 */
	if ((!file->f_op->fallocate) ||
	    lo->lo_encrypt_key_size) {
		q->limits.discard_granularity = 0;
		q->limits.discard_alignment = 0;
		blk_queue_max_discard_sectors(q, 0);
		blk_queue_max_write_zeroes_sectors(q, 0);
		blk_queue_flag_clear(QUEUE_FLAG_DISCARD, q);
		return;
	}

	q->limits.discard_granularity = inode->i_sb->s_blocksize;
	q->limits.discard_alignment = 0;

	blk_queue_max_discard_sectors(q, UINT_MAX >> 9);
	blk_queue_max_write_zeroes_sectors(q, UINT_MAX >> 9);
	blk_queue_flag_set(QUEUE_FLAG_DISCARD, q);
}