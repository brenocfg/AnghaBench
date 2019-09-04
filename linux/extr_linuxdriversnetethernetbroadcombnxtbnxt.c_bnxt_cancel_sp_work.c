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
struct bnxt {int /*<<< orphan*/  sp_task; } ;

/* Variables and functions */
 scalar_t__ BNXT_PF (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_pf_wq ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_cancel_sp_work(struct bnxt *bp)
{
	if (BNXT_PF(bp))
		flush_workqueue(bnxt_pf_wq);
	else
		cancel_work_sync(&bp->sp_task);
}