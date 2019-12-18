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
struct pblk_rb {int /*<<< orphan*/  nr_entries; int /*<<< orphan*/  sync; int /*<<< orphan*/  mem; } ;

/* Variables and functions */
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned int pblk_rb_ring_space (struct pblk_rb*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int pblk_rb_space(struct pblk_rb *rb)
{
	unsigned int mem = READ_ONCE(rb->mem);
	unsigned int sync = READ_ONCE(rb->sync);

	return pblk_rb_ring_space(rb, mem, sync, rb->nr_entries);
}