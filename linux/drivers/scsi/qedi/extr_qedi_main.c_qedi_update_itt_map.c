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
typedef  size_t u32 ;
struct qedi_ctx {TYPE_1__* itt_map; int /*<<< orphan*/  dbg_ctx; } ;
struct qedi_cmd {int dummy; } ;
struct TYPE_2__ {size_t itt; struct qedi_cmd* p_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDI_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t,size_t) ; 
 int /*<<< orphan*/  QEDI_LOG_CONN ; 

void qedi_update_itt_map(struct qedi_ctx *qedi, u32 tid, u32 proto_itt,
			 struct qedi_cmd *cmd)
{
	qedi->itt_map[tid].itt = proto_itt;
	qedi->itt_map[tid].p_cmd = cmd;

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_CONN,
		  "update itt map tid=0x%x, with proto itt=0x%x\n", tid,
		  qedi->itt_map[tid].itt);
}