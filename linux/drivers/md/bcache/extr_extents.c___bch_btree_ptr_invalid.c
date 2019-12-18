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
struct cache_set {int dummy; } ;
struct bkey {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ KEY_DIRTY (struct bkey const*) ; 
 int /*<<< orphan*/  KEY_PTRS (struct bkey const*) ; 
 int /*<<< orphan*/  KEY_SIZE (struct bkey const*) ; 
 scalar_t__ __ptr_invalid (struct cache_set*,struct bkey const*) ; 
 int /*<<< orphan*/  bch_extent_to_text (char*,int,struct bkey const*) ; 
 int /*<<< orphan*/  bch_ptr_status (struct cache_set*,struct bkey const*) ; 
 int /*<<< orphan*/  cache_bug (struct cache_set*,char*,char*,int /*<<< orphan*/ ) ; 

bool __bch_btree_ptr_invalid(struct cache_set *c, const struct bkey *k)
{
	char buf[80];

	if (!KEY_PTRS(k) || !KEY_SIZE(k) || KEY_DIRTY(k))
		goto bad;

	if (__ptr_invalid(c, k))
		goto bad;

	return false;
bad:
	bch_extent_to_text(buf, sizeof(buf), k);
	cache_bug(c, "spotted btree ptr %s: %s", buf, bch_ptr_status(c, k));
	return true;
}