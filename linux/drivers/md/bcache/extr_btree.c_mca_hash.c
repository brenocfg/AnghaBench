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
struct hlist_head {int dummy; } ;
struct cache_set {struct hlist_head* bucket_hash; } ;
struct bkey {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUCKET_HASH_BITS ; 
 int /*<<< orphan*/  PTR_HASH (struct cache_set*,struct bkey*) ; 
 size_t hash_32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct hlist_head *mca_hash(struct cache_set *c, struct bkey *k)
{
	return &c->bucket_hash[hash_32(PTR_HASH(c, k), BUCKET_HASH_BITS)];
}