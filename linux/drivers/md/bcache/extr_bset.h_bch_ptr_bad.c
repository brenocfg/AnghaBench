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
struct btree_keys {TYPE_1__* ops; } ;
struct bkey {int dummy; } ;
struct TYPE_2__ {int (* key_bad ) (struct btree_keys*,struct bkey const*) ;} ;

/* Variables and functions */
 int stub1 (struct btree_keys*,struct bkey const*) ; 

__attribute__((used)) static inline bool bch_ptr_bad(struct btree_keys *b, const struct bkey *k)
{
	return b->ops->key_bad(b, k);
}