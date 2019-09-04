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
struct work_struct {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  include_in_deferred_work; } ;
struct TYPE_9__ {TYPE_3__ cmn; } ;
struct TYPE_6__ {int /*<<< orphan*/  include_in_deferred_work; } ;
struct TYPE_7__ {TYPE_1__ cmn; } ;
struct TYPE_10__ {TYPE_4__ dbgbus_vbif_rt; TYPE_2__ dbgbus_dpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  _dpu_dump_array (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ dpu_dbg_base ; 

__attribute__((used)) static void _dpu_dump_work(struct work_struct *work)
{
	_dpu_dump_array("dpudump_workitem",
		dpu_dbg_base.dbgbus_dpu.cmn.include_in_deferred_work,
		dpu_dbg_base.dbgbus_vbif_rt.cmn.include_in_deferred_work);
}