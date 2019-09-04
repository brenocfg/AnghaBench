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
struct cache_set {int /*<<< orphan*/  bucket_lock; } ;
struct bkey {int dummy; } ;

/* Variables and functions */
 int __bch_bucket_alloc_set (struct cache_set*,unsigned int,struct bkey*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int bch_bucket_alloc_set(struct cache_set *c, unsigned int reserve,
			 struct bkey *k, int n, bool wait)
{
	int ret;

	mutex_lock(&c->bucket_lock);
	ret = __bch_bucket_alloc_set(c, reserve, k, n, wait);
	mutex_unlock(&c->bucket_lock);
	return ret;
}