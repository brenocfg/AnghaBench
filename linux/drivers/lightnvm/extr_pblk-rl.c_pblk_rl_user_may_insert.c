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
struct pblk_rl {int rb_user_max; int /*<<< orphan*/  rb_space; int /*<<< orphan*/  rb_user_cnt; } ;

/* Variables and functions */
 int NVM_IO_ERR ; 
 int NVM_IO_OK ; 
 int NVM_IO_REQUEUE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int pblk_rl_user_may_insert(struct pblk_rl *rl, int nr_entries)
{
	int rb_user_cnt = atomic_read(&rl->rb_user_cnt);
	int rb_space = atomic_read(&rl->rb_space);

	if (unlikely(rb_space >= 0) && (rb_space - nr_entries < 0))
		return NVM_IO_ERR;

	if (rb_user_cnt >= rl->rb_user_max)
		return NVM_IO_REQUEUE;

	return NVM_IO_OK;
}