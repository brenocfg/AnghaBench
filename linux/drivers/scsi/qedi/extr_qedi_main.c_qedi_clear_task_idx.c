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
struct qedi_ctx {int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/  task_idx_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDI_ERR (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  test_and_clear_bit (int,int /*<<< orphan*/ ) ; 

void qedi_clear_task_idx(struct qedi_ctx *qedi, int idx)
{
	if (!test_and_clear_bit(idx, qedi->task_idx_map))
		QEDI_ERR(&qedi->dbg_ctx,
			 "FW task context, already cleared, tid=0x%x\n", idx);
}