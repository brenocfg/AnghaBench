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
struct nvkm_clk {int /*<<< orphan*/  waiting; int /*<<< orphan*/  wait; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nvkm_pstate_calc(struct nvkm_clk *clk, bool wait)
{
	atomic_set(&clk->waiting, 1);
	schedule_work(&clk->work);
	if (wait)
		wait_event(clk->wait, !atomic_read(&clk->waiting));
	return 0;
}