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
struct TYPE_2__ {int /*<<< orphan*/  class_dev; } ;
struct request_queue {TYPE_1__ bsg_dev; } ;
struct inode {int /*<<< orphan*/  i_rdev; } ;
struct file {int dummy; } ;
struct bsg_device {int /*<<< orphan*/  max_queue; int /*<<< orphan*/  name; int /*<<< orphan*/  dev_list; int /*<<< orphan*/  ref_count; struct request_queue* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENXIO ; 
 struct bsg_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_get_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_put_queue (struct request_queue*) ; 
 struct bsg_device* bsg_alloc_device () ; 
 int /*<<< orphan*/  bsg_dbg (struct bsg_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsg_dev_idx_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsg_mutex ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_dev_t (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct bsg_device *bsg_add_device(struct inode *inode,
					 struct request_queue *rq,
					 struct file *file)
{
	struct bsg_device *bd;
	unsigned char buf[32];

	lockdep_assert_held(&bsg_mutex);

	if (!blk_get_queue(rq))
		return ERR_PTR(-ENXIO);

	bd = bsg_alloc_device();
	if (!bd) {
		blk_put_queue(rq);
		return ERR_PTR(-ENOMEM);
	}

	bd->queue = rq;

	refcount_set(&bd->ref_count, 1);
	hlist_add_head(&bd->dev_list, bsg_dev_idx_hash(iminor(inode)));

	strncpy(bd->name, dev_name(rq->bsg_dev.class_dev), sizeof(bd->name) - 1);
	bsg_dbg(bd, "bound to <%s>, max queue %d\n",
		format_dev_t(buf, inode->i_rdev), bd->max_queue);

	return bd;
}