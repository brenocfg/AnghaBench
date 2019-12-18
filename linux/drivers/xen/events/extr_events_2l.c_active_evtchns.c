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
typedef  int xen_ulong_t ;
struct shared_info {int* evtchn_pending; int* evtchn_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_evtchn_mask ; 
 int* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline xen_ulong_t active_evtchns(unsigned int cpu,
					 struct shared_info *sh,
					 unsigned int idx)
{
	return sh->evtchn_pending[idx] &
		per_cpu(cpu_evtchn_mask, cpu)[idx] &
		~sh->evtchn_mask[idx];
}