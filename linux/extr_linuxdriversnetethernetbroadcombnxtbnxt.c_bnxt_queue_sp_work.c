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
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnxt_queue_sp_work(struct bnxt *bp)
{
	if (BNXT_PF(bp))
		queue_work(bnxt_pf_wq, &bp->sp_task);
	else
		schedule_work(&bp->sp_task);
}