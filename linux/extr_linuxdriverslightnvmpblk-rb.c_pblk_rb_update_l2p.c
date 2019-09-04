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
struct pblk_rb {int /*<<< orphan*/  nr_entries; int /*<<< orphan*/  l2p_update; int /*<<< orphan*/  w_lock; } ;

/* Variables and functions */
 int __pblk_rb_update_l2p (struct pblk_rb*,unsigned int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 unsigned int pblk_rb_ring_space (struct pblk_rb*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pblk_rb_update_l2p(struct pblk_rb *rb, unsigned int nr_entries,
			      unsigned int mem, unsigned int sync)
{
	unsigned int space, count;
	int ret = 0;

	lockdep_assert_held(&rb->w_lock);

	/* Update l2p only as buffer entries are being overwritten */
	space = pblk_rb_ring_space(rb, mem, rb->l2p_update, rb->nr_entries);
	if (space > nr_entries)
		goto out;

	count = nr_entries - space;
	/* l2p_update used exclusively under rb->w_lock */
	ret = __pblk_rb_update_l2p(rb, count);

out:
	return ret;
}