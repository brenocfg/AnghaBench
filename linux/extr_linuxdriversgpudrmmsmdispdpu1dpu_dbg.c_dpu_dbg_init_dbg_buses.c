#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {void* entries_size; void* flags; } ;
struct TYPE_4__ {TYPE_1__ cmn; void* entries; } ;
struct dpu_dbg_base {TYPE_2__ dbgbus_vbif_rt; TYPE_2__ dbgbus_dpu; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 void* DBGBUS_FLAGS_DSPP ; 
 scalar_t__ IS_MSM8998_TARGET (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_SDM670_TARGET (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_SDM845_TARGET (int /*<<< orphan*/ ) ; 
 void* dbg_bus_dpu_8998 ; 
 void* dbg_bus_dpu_sdm845 ; 
 struct dpu_dbg_base dpu_dbg_base ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 void* vbif_dbg_bus_msm8998 ; 

void dpu_dbg_init_dbg_buses(u32 hwversion)
{
	static struct dpu_dbg_base *dbg = &dpu_dbg_base;

	memset(&dbg->dbgbus_dpu, 0, sizeof(dbg->dbgbus_dpu));
	memset(&dbg->dbgbus_vbif_rt, 0, sizeof(dbg->dbgbus_vbif_rt));

	if (IS_MSM8998_TARGET(hwversion)) {
		dbg->dbgbus_dpu.entries = dbg_bus_dpu_8998;
		dbg->dbgbus_dpu.cmn.entries_size = ARRAY_SIZE(dbg_bus_dpu_8998);
		dbg->dbgbus_dpu.cmn.flags = DBGBUS_FLAGS_DSPP;

		dbg->dbgbus_vbif_rt.entries = vbif_dbg_bus_msm8998;
		dbg->dbgbus_vbif_rt.cmn.entries_size =
				ARRAY_SIZE(vbif_dbg_bus_msm8998);
	} else if (IS_SDM845_TARGET(hwversion) || IS_SDM670_TARGET(hwversion)) {
		dbg->dbgbus_dpu.entries = dbg_bus_dpu_sdm845;
		dbg->dbgbus_dpu.cmn.entries_size =
				ARRAY_SIZE(dbg_bus_dpu_sdm845);
		dbg->dbgbus_dpu.cmn.flags = DBGBUS_FLAGS_DSPP;

		/* vbif is unchanged vs 8998 */
		dbg->dbgbus_vbif_rt.entries = vbif_dbg_bus_msm8998;
		dbg->dbgbus_vbif_rt.cmn.entries_size =
				ARRAY_SIZE(vbif_dbg_bus_msm8998);
	} else {
		pr_err("unsupported chipset id %X\n", hwversion);
	}
}