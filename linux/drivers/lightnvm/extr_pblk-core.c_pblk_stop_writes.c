#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pblk_line {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  free_lock; } ;
struct pblk {int /*<<< orphan*/  state; TYPE_1__ l_mg; } ;

/* Variables and functions */
 int /*<<< orphan*/  PBLK_STATE_STOPPING ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_disk_name (struct pblk*) ; 
 int /*<<< orphan*/  pblk_set_space_limit (struct pblk*) ; 
 int /*<<< orphan*/  trace_pblk_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pblk_stop_writes(struct pblk *pblk, struct pblk_line *line)
{
	lockdep_assert_held(&pblk->l_mg.free_lock);

	pblk_set_space_limit(pblk);
	pblk->state = PBLK_STATE_STOPPING;
	trace_pblk_state(pblk_disk_name(pblk), pblk->state);
}