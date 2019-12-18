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
struct timer_list {int dummy; } ;
struct pblk {int dummy; } ;

/* Variables and functions */
 struct pblk* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct pblk* pblk ; 
 int /*<<< orphan*/  pblk_write_kick (struct pblk*) ; 
 int /*<<< orphan*/  wtimer ; 

void pblk_write_timer_fn(struct timer_list *t)
{
	struct pblk *pblk = from_timer(pblk, t, wtimer);

	/* kick the write thread every tick to flush outstanding data */
	pblk_write_kick(pblk);
}