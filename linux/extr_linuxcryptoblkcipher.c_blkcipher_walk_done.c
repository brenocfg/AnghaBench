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
struct blkcipher_walk {int nbytes; scalar_t__ total; int flags; scalar_t__ iv; scalar_t__ buffer; scalar_t__ page; int /*<<< orphan*/  ivsize; int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
struct blkcipher_desc {scalar_t__ info; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int BLKCIPHER_WALK_SLOW ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  blkcipher_done_fast (struct blkcipher_walk*,unsigned int) ; 
 int /*<<< orphan*/  blkcipher_done_slow (struct blkcipher_walk*,unsigned int) ; 
 int blkcipher_walk_next (struct blkcipher_desc*,struct blkcipher_walk*) ; 
 int /*<<< orphan*/  crypto_yield (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scatterwalk_done (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ unlikely (int) ; 

int blkcipher_walk_done(struct blkcipher_desc *desc,
			struct blkcipher_walk *walk, int err)
{
	unsigned int n; /* bytes processed */
	bool more;

	if (unlikely(err < 0))
		goto finish;

	n = walk->nbytes - err;
	walk->total -= n;
	more = (walk->total != 0);

	if (likely(!(walk->flags & BLKCIPHER_WALK_SLOW))) {
		blkcipher_done_fast(walk, n);
	} else {
		if (WARN_ON(err)) {
			/* unexpected case; didn't process all bytes */
			err = -EINVAL;
			goto finish;
		}
		blkcipher_done_slow(walk, n);
	}

	scatterwalk_done(&walk->in, 0, more);
	scatterwalk_done(&walk->out, 1, more);

	if (more) {
		crypto_yield(desc->flags);
		return blkcipher_walk_next(desc, walk);
	}
	err = 0;
finish:
	walk->nbytes = 0;
	if (walk->iv != desc->info)
		memcpy(desc->info, walk->iv, walk->ivsize);
	if (walk->buffer != walk->page)
		kfree(walk->buffer);
	if (walk->page)
		free_page((unsigned long)walk->page);
	return err;
}