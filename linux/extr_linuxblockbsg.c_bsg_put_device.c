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
struct request_queue {int dummy; } ;
struct bsg_device {int /*<<< orphan*/  dev_list; int /*<<< orphan*/  ref_count; struct request_queue* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_put_queue (struct request_queue*) ; 
 int /*<<< orphan*/  bsg_dbg (struct bsg_device*,char*) ; 
 int /*<<< orphan*/  bsg_mutex ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct bsg_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bsg_put_device(struct bsg_device *bd)
{
	struct request_queue *q = bd->queue;

	mutex_lock(&bsg_mutex);

	if (!refcount_dec_and_test(&bd->ref_count)) {
		mutex_unlock(&bsg_mutex);
		return 0;
	}

	hlist_del(&bd->dev_list);
	mutex_unlock(&bsg_mutex);

	bsg_dbg(bd, "tearing down\n");

	/*
	 * close can always block
	 */
	kfree(bd);
	blk_put_queue(q);
	return 0;
}