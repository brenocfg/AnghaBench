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
struct pblk_rl {int /*<<< orphan*/  rb_space; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void pblk_rl_inserted(struct pblk_rl *rl, int nr_entries)
{
	int rb_space = atomic_read(&rl->rb_space);

	if (unlikely(rb_space >= 0))
		atomic_sub(nr_entries, &rl->rb_space);
}