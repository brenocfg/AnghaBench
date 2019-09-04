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
struct pblk_rb {int /*<<< orphan*/  nr_entries; int /*<<< orphan*/  subm; int /*<<< orphan*/  mem; } ;

/* Variables and functions */
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned int pblk_rb_ring_count (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

unsigned int pblk_rb_read_count(struct pblk_rb *rb)
{
	unsigned int mem = READ_ONCE(rb->mem);
	unsigned int subm = READ_ONCE(rb->subm);

	return pblk_rb_ring_count(mem, subm, rb->nr_entries);
}