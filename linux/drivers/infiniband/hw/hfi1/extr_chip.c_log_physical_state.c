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
struct hfi1_pportdata {int /*<<< orphan*/  dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  dd_dev_err (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  log_state_transition (struct hfi1_pportdata*,scalar_t__) ; 
 scalar_t__ read_physical_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void log_physical_state(struct hfi1_pportdata *ppd, u32 state)
{
	u32 read_state = read_physical_state(ppd->dd);

	if (read_state == state) {
		log_state_transition(ppd, state);
	} else {
		dd_dev_err(ppd->dd,
			   "anticipated phy link state 0x%x, read 0x%x\n",
			   state, read_state);
	}
}