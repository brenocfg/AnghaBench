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
struct TYPE_4__ {TYPE_1__* mpt; } ;
struct TYPE_3__ {unsigned long (* from_virt_to_mfn ) (void*) ;} ;

/* Variables and functions */
 TYPE_2__ intel_gvt_host ; 
 unsigned long stub1 (void*) ; 

__attribute__((used)) static inline unsigned long intel_gvt_hypervisor_virt_to_mfn(void *p)
{
	return intel_gvt_host.mpt->from_virt_to_mfn(p);
}