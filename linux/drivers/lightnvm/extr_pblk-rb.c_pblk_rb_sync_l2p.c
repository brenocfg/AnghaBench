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
struct pblk_rb {int /*<<< orphan*/  w_lock; int /*<<< orphan*/  nr_entries; int /*<<< orphan*/  l2p_update; int /*<<< orphan*/  sync; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pblk_rb_update_l2p (struct pblk_rb*,unsigned int) ; 
 unsigned int pblk_rb_ring_count (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int smp_load_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void pblk_rb_sync_l2p(struct pblk_rb *rb)
{
	unsigned int sync;
	unsigned int to_update;

	spin_lock(&rb->w_lock);

	/* Protect from reads and writes */
	sync = smp_load_acquire(&rb->sync);

	to_update = pblk_rb_ring_count(sync, rb->l2p_update, rb->nr_entries);
	__pblk_rb_update_l2p(rb, to_update);

	spin_unlock(&rb->w_lock);
}