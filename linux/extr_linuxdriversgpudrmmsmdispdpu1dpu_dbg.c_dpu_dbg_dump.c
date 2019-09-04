#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int include_in_deferred_work; } ;
struct TYPE_9__ {TYPE_3__ cmn; } ;
struct TYPE_6__ {int include_in_deferred_work; } ;
struct TYPE_7__ {TYPE_1__ cmn; } ;
struct TYPE_10__ {int /*<<< orphan*/  dump_work; TYPE_4__ dbgbus_vbif_rt; TYPE_2__ dbgbus_dpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  _dpu_dump_array (char const*,int,int) ; 
 TYPE_5__ dpu_dbg_base ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ work_pending (int /*<<< orphan*/ *) ; 

void dpu_dbg_dump(bool queue_work, const char *name, bool dump_dbgbus_dpu,
		  bool dump_dbgbus_vbif_rt)
{
	if (queue_work && work_pending(&dpu_dbg_base.dump_work))
		return;

	if (!queue_work) {
		_dpu_dump_array(name, dump_dbgbus_dpu, dump_dbgbus_vbif_rt);
		return;
	}

	/* schedule work to dump later */
	dpu_dbg_base.dbgbus_dpu.cmn.include_in_deferred_work = dump_dbgbus_dpu;
	dpu_dbg_base.dbgbus_vbif_rt.cmn.include_in_deferred_work =
			dump_dbgbus_vbif_rt;
	schedule_work(&dpu_dbg_base.dump_work);
}