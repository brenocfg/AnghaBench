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
typedef  int /*<<< orphan*/  u64 ;
struct hw_perf_event {int dummy; } ;
struct cpu_hw_events {int /*<<< orphan*/ * pcr; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* write_pcr ) (int,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int num_pcrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  mask_for_index (int) ; 
 int /*<<< orphan*/  nop_for_index (int) ; 
 TYPE_2__* pcr_ops ; 
 TYPE_1__* sparc_pmu ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sparc_pmu_disable_event(struct cpu_hw_events *cpuc, struct hw_perf_event *hwc, int idx)
{
	u64 mask = mask_for_index(idx);
	u64 nop = nop_for_index(idx);
	int pcr_index = 0;
	u64 val;

	if (sparc_pmu->num_pcrs > 1)
		pcr_index = idx;

	val = cpuc->pcr[pcr_index];
	val &= ~mask;
	val |= nop;
	cpuc->pcr[pcr_index] = val;

	pcr_ops->write_pcr(pcr_index, cpuc->pcr[pcr_index]);
}