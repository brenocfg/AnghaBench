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
struct pblk_rb {unsigned int back_thres; int /*<<< orphan*/  nr_entries; int /*<<< orphan*/  mem; int /*<<< orphan*/  sync; } ;

/* Variables and functions */
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned int pblk_rb_ring_space (struct pblk_rb*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ pblk_rb_update_l2p (struct pblk_rb*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int __pblk_rb_may_write(struct pblk_rb *rb, unsigned int nr_entries,
			       unsigned int *pos)
{
	unsigned int mem;
	unsigned int sync;
	unsigned int threshold;

	sync = READ_ONCE(rb->sync);
	mem = READ_ONCE(rb->mem);

	threshold = nr_entries + rb->back_thres;

	if (pblk_rb_ring_space(rb, mem, sync, rb->nr_entries) < threshold)
		return 0;

	if (pblk_rb_update_l2p(rb, nr_entries, mem, sync))
		return 0;

	*pos = mem;

	return 1;
}