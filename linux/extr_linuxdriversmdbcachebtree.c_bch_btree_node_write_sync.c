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
struct closure {int dummy; } ;
struct btree {int /*<<< orphan*/  write_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  bch_btree_node_write (struct btree*,struct closure*) ; 
 int /*<<< orphan*/  closure_init_stack (struct closure*) ; 
 int /*<<< orphan*/  closure_sync (struct closure*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bch_btree_node_write_sync(struct btree *b)
{
	struct closure cl;

	closure_init_stack(&cl);

	mutex_lock(&b->write_lock);
	bch_btree_node_write(b, &cl);
	mutex_unlock(&b->write_lock);

	closure_sync(&cl);
}