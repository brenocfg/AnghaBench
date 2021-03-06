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
struct msm_mmu {int (* handler ) (void*,unsigned long,int) ;void* arg; } ;

/* Variables and functions */

__attribute__((used)) static inline void msm_mmu_set_fault_handler(struct msm_mmu *mmu, void *arg,
		int (*handler)(void *arg, unsigned long iova, int flags))
{
	mmu->arg = arg;
	mmu->handler = handler;
}