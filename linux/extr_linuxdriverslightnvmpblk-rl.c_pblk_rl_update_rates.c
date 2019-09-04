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
struct pblk_rl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pblk_rl_update_rates (struct pblk_rl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_rl_nr_user_free_blks (struct pblk_rl*) ; 

void pblk_rl_update_rates(struct pblk_rl *rl)
{
	__pblk_rl_update_rates(rl, pblk_rl_nr_user_free_blks(rl));
}