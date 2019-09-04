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
struct TYPE_2__ {int /*<<< orphan*/  dbgbus_vbif_rt; int /*<<< orphan*/  dbgbus_dpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  _dpu_dbg_dump_dpu_dbg_bus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _dpu_dbg_dump_vbif_dbg_bus (int /*<<< orphan*/ *) ; 
 TYPE_1__ dpu_dbg_base ; 

__attribute__((used)) static void _dpu_dump_array(const char *name, bool dump_dbgbus_dpu,
			    bool dump_dbgbus_vbif_rt)
{
	if (dump_dbgbus_dpu)
		_dpu_dbg_dump_dpu_dbg_bus(&dpu_dbg_base.dbgbus_dpu);

	if (dump_dbgbus_vbif_rt)
		_dpu_dbg_dump_vbif_dbg_bus(&dpu_dbg_base.dbgbus_vbif_rt);
}