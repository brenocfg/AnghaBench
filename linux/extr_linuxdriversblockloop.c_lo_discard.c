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
struct request {int dummy; } ;
struct loop_device {scalar_t__ lo_encrypt_key_size; struct file* lo_backing_file; } ;
struct file {TYPE_1__* f_op; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int (* fallocate ) (struct file*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 int FALLOC_FL_KEEP_SIZE ; 
 int FALLOC_FL_PUNCH_HOLE ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 int stub1 (struct file*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int lo_discard(struct loop_device *lo, struct request *rq, loff_t pos)
{
	/*
	 * We use punch hole to reclaim the free space used by the
	 * image a.k.a. discard. However we do not support discard if
	 * encryption is enabled, because it may give an attacker
	 * useful information.
	 */
	struct file *file = lo->lo_backing_file;
	int mode = FALLOC_FL_PUNCH_HOLE | FALLOC_FL_KEEP_SIZE;
	int ret;

	if ((!file->f_op->fallocate) || lo->lo_encrypt_key_size) {
		ret = -EOPNOTSUPP;
		goto out;
	}

	ret = file->f_op->fallocate(file, mode, pos, blk_rq_bytes(rq));
	if (unlikely(ret && ret != -EINVAL && ret != -EOPNOTSUPP))
		ret = -EIO;
 out:
	return ret;
}