#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct loop_device {unsigned int lo_offset; int use_dio; int /*<<< orphan*/  lo_queue; int /*<<< orphan*/  lo_flags; int /*<<< orphan*/  transfer; struct file* lo_backing_file; } ;
struct inode {TYPE_1__* i_sb; } ;
struct file {struct address_space* f_mapping; } ;
struct address_space {TYPE_2__* a_ops; struct inode* host; } ;
struct TYPE_4__ {scalar_t__ direct_IO; } ;
struct TYPE_3__ {scalar_t__ s_bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LO_FLAGS_DIRECT_IO ; 
 int /*<<< orphan*/  QUEUE_FLAG_NOMERGES ; 
 unsigned short bdev_logical_block_size (scalar_t__) ; 
 int /*<<< orphan*/  blk_mq_freeze_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_unfreeze_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_flag_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned short queue_logical_block_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_fsync (struct file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __loop_update_dio(struct loop_device *lo, bool dio)
{
	struct file *file = lo->lo_backing_file;
	struct address_space *mapping = file->f_mapping;
	struct inode *inode = mapping->host;
	unsigned short sb_bsize = 0;
	unsigned dio_align = 0;
	bool use_dio;

	if (inode->i_sb->s_bdev) {
		sb_bsize = bdev_logical_block_size(inode->i_sb->s_bdev);
		dio_align = sb_bsize - 1;
	}

	/*
	 * We support direct I/O only if lo_offset is aligned with the
	 * logical I/O size of backing device, and the logical block
	 * size of loop is bigger than the backing device's and the loop
	 * needn't transform transfer.
	 *
	 * TODO: the above condition may be loosed in the future, and
	 * direct I/O may be switched runtime at that time because most
	 * of requests in sane applications should be PAGE_SIZE aligned
	 */
	if (dio) {
		if (queue_logical_block_size(lo->lo_queue) >= sb_bsize &&
				!(lo->lo_offset & dio_align) &&
				mapping->a_ops->direct_IO &&
				!lo->transfer)
			use_dio = true;
		else
			use_dio = false;
	} else {
		use_dio = false;
	}

	if (lo->use_dio == use_dio)
		return;

	/* flush dirty pages before changing direct IO */
	vfs_fsync(file, 0);

	/*
	 * The flag of LO_FLAGS_DIRECT_IO is handled similarly with
	 * LO_FLAGS_READ_ONLY, both are set from kernel, and losetup
	 * will get updated by ioctl(LOOP_GET_STATUS)
	 */
	blk_mq_freeze_queue(lo->lo_queue);
	lo->use_dio = use_dio;
	if (use_dio) {
		blk_queue_flag_clear(QUEUE_FLAG_NOMERGES, lo->lo_queue);
		lo->lo_flags |= LO_FLAGS_DIRECT_IO;
	} else {
		blk_queue_flag_set(QUEUE_FLAG_NOMERGES, lo->lo_queue);
		lo->lo_flags &= ~LO_FLAGS_DIRECT_IO;
	}
	blk_mq_unfreeze_queue(lo->lo_queue);
}