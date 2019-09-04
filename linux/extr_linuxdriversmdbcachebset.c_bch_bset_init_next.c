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
typedef  int /*<<< orphan*/  uint64_t ;
struct btree_keys {size_t nsets; TYPE_1__* set; } ;
struct bset {scalar_t__ keys; scalar_t__ version; int /*<<< orphan*/  magic; int /*<<< orphan*/  seq; } ;
struct TYPE_2__ {struct bset* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  bch_bset_build_unwritten_tree (struct btree_keys*) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 

void bch_bset_init_next(struct btree_keys *b, struct bset *i, uint64_t magic)
{
	if (i != b->set->data) {
		b->set[++b->nsets].data = i;
		i->seq = b->set->data->seq;
	} else
		get_random_bytes(&i->seq, sizeof(uint64_t));

	i->magic	= magic;
	i->version	= 0;
	i->keys		= 0;

	bch_bset_build_unwritten_tree(b);
}