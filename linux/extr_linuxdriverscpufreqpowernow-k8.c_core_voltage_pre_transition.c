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
typedef  scalar_t__ u32 ;
struct powernow_k8_data {scalar_t__ rvo; scalar_t__ currfid; scalar_t__ currvid; int vidmvs; } ;

/* Variables and functions */
 scalar_t__ LO_FID_TABLE_TOP ; 
 int /*<<< orphan*/  MSR_FIDVID_STATUS ; 
 scalar_t__ decrease_vid_code_by_step (struct powernow_k8_data*,int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 scalar_t__ query_current_values_with_pending_wait (struct powernow_k8_data*) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static int core_voltage_pre_transition(struct powernow_k8_data *data,
		u32 reqvid, u32 reqfid)
{
	u32 rvosteps = data->rvo;
	u32 savefid = data->currfid;
	u32 maxvid, lo, rvomult = 1;

	pr_debug("ph1 (cpu%d): start, currfid 0x%x, currvid 0x%x, reqvid 0x%x, rvo 0x%x\n",
		smp_processor_id(),
		data->currfid, data->currvid, reqvid, data->rvo);

	if ((savefid < LO_FID_TABLE_TOP) && (reqfid < LO_FID_TABLE_TOP))
		rvomult = 2;
	rvosteps *= rvomult;
	rdmsr(MSR_FIDVID_STATUS, lo, maxvid);
	maxvid = 0x1f & (maxvid >> 16);
	pr_debug("ph1 maxvid=0x%x\n", maxvid);
	if (reqvid < maxvid) /* lower numbers are higher voltages */
		reqvid = maxvid;

	while (data->currvid > reqvid) {
		pr_debug("ph1: curr 0x%x, req vid 0x%x\n",
			data->currvid, reqvid);
		if (decrease_vid_code_by_step(data, reqvid, data->vidmvs))
			return 1;
	}

	while ((rvosteps > 0) &&
			((rvomult * data->rvo + data->currvid) > reqvid)) {
		if (data->currvid == maxvid) {
			rvosteps = 0;
		} else {
			pr_debug("ph1: changing vid for rvo, req 0x%x\n",
				data->currvid - 1);
			if (decrease_vid_code_by_step(data, data->currvid-1, 1))
				return 1;
			rvosteps--;
		}
	}

	if (query_current_values_with_pending_wait(data))
		return 1;

	if (savefid != data->currfid) {
		pr_err("ph1 err, currfid changed 0x%x\n", data->currfid);
		return 1;
	}

	pr_debug("ph1 complete, currfid 0x%x, currvid 0x%x\n",
		data->currfid, data->currvid);

	return 0;
}