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
struct hfi1_pportdata {scalar_t__* pkeys; int /*<<< orphan*/  port; int /*<<< orphan*/  dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI1_IB_CFG_PKEYS ; 
 int /*<<< orphan*/  hfi1_event_pkey_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_set_ib_cfg (struct hfi1_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clear_full_mgmt_pkey(struct hfi1_pportdata *ppd)
{
	if (ppd->pkeys[2] != 0) {
		ppd->pkeys[2] = 0;
		(void)hfi1_set_ib_cfg(ppd, HFI1_IB_CFG_PKEYS, 0);
		hfi1_event_pkey_change(ppd->dd, ppd->port);
	}
}