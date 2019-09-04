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
struct pblk_rb {int nr_entries; int /*<<< orphan*/  mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pblk_rb_may_write (struct pblk_rb*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int pblk_rb_may_write(struct pblk_rb *rb, unsigned int nr_entries,
			     unsigned int *pos)
{
	if (!__pblk_rb_may_write(rb, nr_entries, pos))
		return 0;

	/* Protect from read count */
	smp_store_release(&rb->mem, (*pos + nr_entries) & (rb->nr_entries - 1));
	return 1;
}