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
struct pblk {int /*<<< orphan*/  rl; } ;

/* Variables and functions */
 int /*<<< orphan*/  pblk_rl_update_rates (int /*<<< orphan*/ *) ; 

void pblk_gc_should_kick(struct pblk *pblk)
{
	pblk_rl_update_rates(&pblk->rl);
}