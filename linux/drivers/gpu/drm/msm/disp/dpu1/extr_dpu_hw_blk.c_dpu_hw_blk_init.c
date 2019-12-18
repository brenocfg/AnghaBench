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
typedef  int /*<<< orphan*/  u32 ;
struct dpu_hw_blk_ops {int dummy; } ;
struct dpu_hw_blk {int id; int /*<<< orphan*/  list; struct dpu_hw_blk_ops ops; int /*<<< orphan*/  refcount; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpu_hw_blk_list ; 
 int /*<<< orphan*/  dpu_hw_blk_lock ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void dpu_hw_blk_init(struct dpu_hw_blk *hw_blk, u32 type, int id,
		struct dpu_hw_blk_ops *ops)
{
	INIT_LIST_HEAD(&hw_blk->list);
	hw_blk->type = type;
	hw_blk->id = id;
	atomic_set(&hw_blk->refcount, 0);

	if (ops)
		hw_blk->ops = *ops;

	mutex_lock(&dpu_hw_blk_lock);
	list_add(&hw_blk->list, &dpu_hw_blk_list);
	mutex_unlock(&dpu_hw_blk_lock);
}