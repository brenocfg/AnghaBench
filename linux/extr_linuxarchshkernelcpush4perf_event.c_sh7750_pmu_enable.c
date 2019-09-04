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
struct hw_perf_event {int config; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMCR (int) ; 
 int PMCR_PMCLR ; 
 int PMCR_PMEN ; 
 int PMCR_PMST ; 
 int __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh7750_pmu_enable(struct hw_perf_event *hwc, int idx)
{
	__raw_writew(__raw_readw(PMCR(idx)) | PMCR_PMCLR, PMCR(idx));
	__raw_writew(hwc->config | PMCR_PMEN | PMCR_PMST, PMCR(idx));
}