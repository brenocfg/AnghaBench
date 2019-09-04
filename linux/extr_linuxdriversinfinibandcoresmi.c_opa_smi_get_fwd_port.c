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
struct TYPE_3__ {int* initial_path; int* return_path; } ;
struct TYPE_4__ {TYPE_1__ dr; } ;
struct opa_smp {int hop_ptr; TYPE_2__ route; } ;

/* Variables and functions */
 int /*<<< orphan*/  opa_get_smp_direction (struct opa_smp*) ; 

int opa_smi_get_fwd_port(struct opa_smp *smp)
{
	return !opa_get_smp_direction(smp) ? smp->route.dr.initial_path[smp->hop_ptr+1] :
		smp->route.dr.return_path[smp->hop_ptr-1];
}