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
struct btree_op {int lock; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct btree_op*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void bch_btree_op_init(struct btree_op *op, int write_lock_level)
{
	memset(op, 0, sizeof(struct btree_op));
	init_wait(&op->wait);
	op->lock = write_lock_level;
}