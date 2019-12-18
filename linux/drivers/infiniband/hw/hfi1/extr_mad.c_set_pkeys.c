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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct hfi1_pportdata {scalar_t__* pkeys; } ;
struct hfi1_devdata {struct hfi1_pportdata* pport; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  HFI1_IB_CFG_PKEYS ; 
 scalar_t__ LIM_MGMT_P_KEY ; 
 int /*<<< orphan*/  hfi1_event_pkey_change (struct hfi1_devdata*,int) ; 
 int /*<<< orphan*/  hfi1_set_ib_cfg (struct hfi1_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_pkeys(struct hfi1_devdata *dd, u8 port, u16 *pkeys)
{
	struct hfi1_pportdata *ppd;
	int i;
	int changed = 0;
	int update_includes_mgmt_partition = 0;

	/*
	 * IB port one/two always maps to context zero/one,
	 * always a kernel context, no locking needed
	 * If we get here with ppd setup, no need to check
	 * that rcd is valid.
	 */
	ppd = dd->pport + (port - 1);
	/*
	 * If the update does not include the management pkey, don't do it.
	 */
	for (i = 0; i < ARRAY_SIZE(ppd->pkeys); i++) {
		if (pkeys[i] == LIM_MGMT_P_KEY) {
			update_includes_mgmt_partition = 1;
			break;
		}
	}

	if (!update_includes_mgmt_partition)
		return 1;

	for (i = 0; i < ARRAY_SIZE(ppd->pkeys); i++) {
		u16 key = pkeys[i];
		u16 okey = ppd->pkeys[i];

		if (key == okey)
			continue;
		/*
		 * The SM gives us the complete PKey table. We have
		 * to ensure that we put the PKeys in the matching
		 * slots.
		 */
		ppd->pkeys[i] = key;
		changed = 1;
	}

	if (changed) {
		(void)hfi1_set_ib_cfg(ppd, HFI1_IB_CFG_PKEYS, 0);
		hfi1_event_pkey_change(dd, port);
	}

	return 0;
}