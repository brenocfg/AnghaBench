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
struct pblk_rb {int nr_entries; int /*<<< orphan*/  subm; } ;

/* Variables and functions */
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,unsigned int) ; 

unsigned int pblk_rb_read_commit(struct pblk_rb *rb, unsigned int nr_entries)
{
	unsigned int subm;

	subm = READ_ONCE(rb->subm);
	/* Commit read means updating submission pointer */
	smp_store_release(&rb->subm,
				(subm + nr_entries) & (rb->nr_entries - 1));

	return subm;
}