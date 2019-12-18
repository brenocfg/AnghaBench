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
struct ib_smp {int* initial_path; int hop_ptr; int* return_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_get_smp_direction (struct ib_smp*) ; 

int smi_get_fwd_port(struct ib_smp *smp)
{
	return (!ib_get_smp_direction(smp) ? smp->initial_path[smp->hop_ptr+1] :
		smp->return_path[smp->hop_ptr-1]);
}