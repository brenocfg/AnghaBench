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

int pblk_rl_is_limit(struct pblk_rl *rl)
{
	int rb_space;

	rb_space = atomic_read(&rl->rb_space);

	return (rb_space == 0);
}