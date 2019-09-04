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
struct pblk_rl {int /*<<< orphan*/  rb_user_active; int /*<<< orphan*/  rb_user_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_rl_kick_u_timer (struct pblk_rl*) ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,int) ; 

void pblk_rl_user_in(struct pblk_rl *rl, int nr_entries)
{
	atomic_add(nr_entries, &rl->rb_user_cnt);

	/* Release user I/O state. Protect from GC */
	smp_store_release(&rl->rb_user_active, 1);
	pblk_rl_kick_u_timer(rl);
}