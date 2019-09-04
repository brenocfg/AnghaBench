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
typedef  int /*<<< orphan*/  u64 ;
struct work_struct {int dummy; } ;
struct hv_tsc_emulation_status {scalar_t__ inprogress; } ;

/* Variables and functions */
 int /*<<< orphan*/  HV_X64_MSR_TSC_EMULATION_STATUS ; 
 int /*<<< orphan*/  hv_reenlightenment_cb () ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hv_reenlightenment_notify(struct work_struct *dummy)
{
	struct hv_tsc_emulation_status emu_status;

	rdmsrl(HV_X64_MSR_TSC_EMULATION_STATUS, *(u64 *)&emu_status);

	/* Don't issue the callback if TSC accesses are not emulated */
	if (hv_reenlightenment_cb && emu_status.inprogress)
		hv_reenlightenment_cb();
}