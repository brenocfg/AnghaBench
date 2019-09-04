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
struct open_bucket {int /*<<< orphan*/  list; } ;
struct cache_set {int /*<<< orphan*/  data_buckets; int /*<<< orphan*/  data_bucket_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_OPEN_BUCKETS ; 
 struct open_bucket* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int bch_open_buckets_alloc(struct cache_set *c)
{
	int i;

	spin_lock_init(&c->data_bucket_lock);

	for (i = 0; i < MAX_OPEN_BUCKETS; i++) {
		struct open_bucket *b = kzalloc(sizeof(*b), GFP_KERNEL);

		if (!b)
			return -ENOMEM;

		list_add(&b->list, &c->data_buckets);
	}

	return 0;
}