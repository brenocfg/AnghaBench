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
struct skcipher_walk {unsigned long alignmask; int /*<<< orphan*/ * page; scalar_t__ iv; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int EDEADLK ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_irq () ; 
 int skcipher_copy_iv (struct skcipher_walk*) ; 
 int skcipher_walk_next (struct skcipher_walk*) ; 
 scalar_t__ unlikely (unsigned long) ; 

__attribute__((used)) static int skcipher_walk_first(struct skcipher_walk *walk)
{
	if (WARN_ON_ONCE(in_irq()))
		return -EDEADLK;

	walk->buffer = NULL;
	if (unlikely(((unsigned long)walk->iv & walk->alignmask))) {
		int err = skcipher_copy_iv(walk);
		if (err)
			return err;
	}

	walk->page = NULL;

	return skcipher_walk_next(walk);
}