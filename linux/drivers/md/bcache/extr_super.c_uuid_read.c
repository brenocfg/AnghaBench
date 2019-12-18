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
struct uuid_entry_v0 {int /*<<< orphan*/  invalidated; int /*<<< orphan*/  last_reg; int /*<<< orphan*/  first_reg; int /*<<< orphan*/  label; int /*<<< orphan*/  uuid; } ;
struct uuid_entry {scalar_t__ sectors; scalar_t__ flags; int /*<<< orphan*/  invalidated; int /*<<< orphan*/  last_reg; int /*<<< orphan*/  first_reg; int /*<<< orphan*/  label; int /*<<< orphan*/  uuid; } ;
struct bkey {int dummy; } ;
struct jset {scalar_t__ version; struct bkey uuid_bucket; } ;
struct closure {int dummy; } ;
struct cache_set {int nr_uuids; scalar_t__ uuids; int /*<<< orphan*/  uuid_bucket; } ;

/* Variables and functions */
 scalar_t__ BCACHE_JSET_VERSION_UUIDv1 ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 scalar_t__ __bch_btree_ptr_invalid (struct cache_set*,struct bkey*) ; 
 int /*<<< orphan*/  bkey_copy (int /*<<< orphan*/ *,struct bkey*) ; 
 int /*<<< orphan*/  closure_sync (struct closure*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uuid_io (struct cache_set*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bkey*,struct closure*) ; 

__attribute__((used)) static char *uuid_read(struct cache_set *c, struct jset *j, struct closure *cl)
{
	struct bkey *k = &j->uuid_bucket;

	if (__bch_btree_ptr_invalid(c, k))
		return "bad uuid pointer";

	bkey_copy(&c->uuid_bucket, k);
	uuid_io(c, REQ_OP_READ, 0, k, cl);

	if (j->version < BCACHE_JSET_VERSION_UUIDv1) {
		struct uuid_entry_v0	*u0 = (void *) c->uuids;
		struct uuid_entry	*u1 = (void *) c->uuids;
		int i;

		closure_sync(cl);

		/*
		 * Since the new uuid entry is bigger than the old, we have to
		 * convert starting at the highest memory address and work down
		 * in order to do it in place
		 */

		for (i = c->nr_uuids - 1;
		     i >= 0;
		     --i) {
			memcpy(u1[i].uuid,	u0[i].uuid, 16);
			memcpy(u1[i].label,	u0[i].label, 32);

			u1[i].first_reg		= u0[i].first_reg;
			u1[i].last_reg		= u0[i].last_reg;
			u1[i].invalidated	= u0[i].invalidated;

			u1[i].flags	= 0;
			u1[i].sectors	= 0;
		}
	}

	return NULL;
}