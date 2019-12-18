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
typedef  int /*<<< orphan*/  u32 ;
struct hfi1_pportdata {int /*<<< orphan*/  dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  chip_to_opa_pstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dd_dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opa_pstate_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void log_state_transition(struct hfi1_pportdata *ppd, u32 state)
{
	u32 ib_pstate = chip_to_opa_pstate(ppd->dd, state);

	dd_dev_info(ppd->dd,
		    "physical state changed to %s (0x%x), phy 0x%x\n",
		    opa_pstate_name(ib_pstate), ib_pstate, state);
}