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
struct crypto_hash_walk {unsigned int alignmask; unsigned int data; unsigned int offset; int flags; int /*<<< orphan*/  sg; int /*<<< orphan*/  total; int /*<<< orphan*/  pg; scalar_t__ entrylen; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,unsigned int) ; 
 int CRYPTO_ALG_ASYNC ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  crypto_yield (int) ; 
 int hash_walk_new_entry (struct crypto_hash_walk*) ; 
 int hash_walk_next (struct crypto_hash_walk*) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (unsigned int) ; 
 unsigned int min (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  sg_next (int /*<<< orphan*/ ) ; 

int crypto_hash_walk_done(struct crypto_hash_walk *walk, int err)
{
	unsigned int alignmask = walk->alignmask;

	walk->data -= walk->offset;

	if (walk->entrylen && (walk->offset & alignmask) && !err) {
		unsigned int nbytes;

		walk->offset = ALIGN(walk->offset, alignmask + 1);
		nbytes = min(walk->entrylen,
			     (unsigned int)(PAGE_SIZE - walk->offset));
		if (nbytes) {
			walk->entrylen -= nbytes;
			walk->data += walk->offset;
			return nbytes;
		}
	}

	if (walk->flags & CRYPTO_ALG_ASYNC)
		kunmap(walk->pg);
	else {
		kunmap_atomic(walk->data);
		/*
		 * The may sleep test only makes sense for sync users.
		 * Async users don't need to sleep here anyway.
		 */
		crypto_yield(walk->flags);
	}

	if (err)
		return err;

	if (walk->entrylen) {
		walk->offset = 0;
		walk->pg++;
		return hash_walk_next(walk);
	}

	if (!walk->total)
		return 0;

	walk->sg = sg_next(walk->sg);

	return hash_walk_new_entry(walk);
}