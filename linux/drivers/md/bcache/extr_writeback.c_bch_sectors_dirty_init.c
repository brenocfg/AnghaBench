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
struct sectors_dirty_init {int /*<<< orphan*/  start; int /*<<< orphan*/  op; int /*<<< orphan*/  inode; scalar_t__ count; } ;
struct bcache_device {int /*<<< orphan*/  c; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  INIT_KEYS_SLEEP_MS ; 
 int /*<<< orphan*/  KEY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bch_btree_map_keys (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bch_btree_op_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sectors_dirty_init_fn ; 

void bch_sectors_dirty_init(struct bcache_device *d)
{
	struct sectors_dirty_init op;
	int ret;

	bch_btree_op_init(&op.op, -1);
	op.inode = d->id;
	op.count = 0;
	op.start = KEY(op.inode, 0, 0);

	do {
		ret = bch_btree_map_keys(&op.op, d->c, &op.start,
					 sectors_dirty_init_fn, 0);
		if (ret == -EAGAIN)
			schedule_timeout_interruptible(
				msecs_to_jiffies(INIT_KEYS_SLEEP_MS));
		else if (ret < 0) {
			pr_warn("sectors dirty init failed, ret=%d!", ret);
			break;
		}
	} while (ret == -EAGAIN);
}