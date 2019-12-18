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
struct nvm_tgt_type {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* exit ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* sysfs_exit ) (struct gendisk*) ;} ;
struct nvm_target {int /*<<< orphan*/  list; struct nvm_tgt_type* type; int /*<<< orphan*/  dev; struct gendisk* disk; } ;
struct gendisk {int /*<<< orphan*/  private_data; struct request_queue* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (struct request_queue*) ; 
 int /*<<< orphan*/  del_gendisk (struct gendisk*) ; 
 int /*<<< orphan*/  kfree (struct nvm_target*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvm_remove_tgt_dev (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 
 int /*<<< orphan*/  stub1 (struct gendisk*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __nvm_remove_target(struct nvm_target *t, bool graceful)
{
	struct nvm_tgt_type *tt = t->type;
	struct gendisk *tdisk = t->disk;
	struct request_queue *q = tdisk->queue;

	del_gendisk(tdisk);
	blk_cleanup_queue(q);

	if (tt->sysfs_exit)
		tt->sysfs_exit(tdisk);

	if (tt->exit)
		tt->exit(tdisk->private_data, graceful);

	nvm_remove_tgt_dev(t->dev, 1);
	put_disk(tdisk);
	module_put(t->type->owner);

	list_del(&t->list);
	kfree(t);
}