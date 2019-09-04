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
typedef  int u32 ;
struct powernow_k8_data {int currvid; int currfid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_FIDVID_STATUS ; 
 int MSR_S_HI_CURRENT_VID ; 
 int MSR_S_LO_CHANGE_PENDING ; 
 int MSR_S_LO_CURRENT_FID ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int query_current_values_with_pending_wait(struct powernow_k8_data *data)
{
	u32 lo, hi;
	u32 i = 0;

	do {
		if (i++ > 10000) {
			pr_debug("detected change pending stuck\n");
			return 1;
		}
		rdmsr(MSR_FIDVID_STATUS, lo, hi);
	} while (lo & MSR_S_LO_CHANGE_PENDING);

	data->currvid = hi & MSR_S_HI_CURRENT_VID;
	data->currfid = lo & MSR_S_LO_CURRENT_FID;

	return 0;
}