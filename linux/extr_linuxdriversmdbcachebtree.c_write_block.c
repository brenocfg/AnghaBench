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
struct btree {int written; int /*<<< orphan*/  c; } ;
typedef  void bset ;

/* Variables and functions */
 int block_bytes (int /*<<< orphan*/ ) ; 
 scalar_t__ btree_bset_first (struct btree*) ; 

__attribute__((used)) static inline struct bset *write_block(struct btree *b)
{
	return ((void *) btree_bset_first(b)) + b->written * block_bytes(b->c);
}