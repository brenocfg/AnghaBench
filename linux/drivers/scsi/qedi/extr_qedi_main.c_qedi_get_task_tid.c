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
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct qedi_ctx {int /*<<< orphan*/  dbg_ctx; TYPE_1__* itt_map; } ;
typedef  size_t s16 ;
struct TYPE_2__ {scalar_t__ itt; } ;

/* Variables and functions */
 size_t MAX_ISCSI_TASK_ENTRIES ; 
 int /*<<< orphan*/  QEDI_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  QEDI_LOG_CONN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

void qedi_get_task_tid(struct qedi_ctx *qedi, u32 itt, s16 *tid)
{
	u16 i;

	for (i = 0; i < MAX_ISCSI_TASK_ENTRIES; i++) {
		if (qedi->itt_map[i].itt == itt) {
			*tid = i;
			QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_CONN,
				  "Ref itt=0x%x, found at tid=0x%x\n",
				  itt, *tid);
			return;
		}
	}

	WARN_ON(1);
}