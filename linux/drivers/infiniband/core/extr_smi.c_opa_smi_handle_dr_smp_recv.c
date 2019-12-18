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
struct TYPE_3__ {scalar_t__ dr_dlid; scalar_t__ dr_slid; int /*<<< orphan*/  return_path; int /*<<< orphan*/  initial_path; } ;
struct TYPE_4__ {TYPE_1__ dr; } ;
struct opa_smp {TYPE_2__ route; int /*<<< orphan*/  hop_cnt; int /*<<< orphan*/  hop_ptr; } ;
typedef  enum smi_action { ____Placeholder_smi_action } smi_action ;

/* Variables and functions */
 scalar_t__ OPA_LID_PERMISSIVE ; 
 int __smi_handle_dr_smp_recv (int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  opa_get_smp_direction (struct opa_smp*) ; 

enum smi_action opa_smi_handle_dr_smp_recv(struct opa_smp *smp, bool is_switch,
					   int port_num, int phys_port_cnt)
{
	return __smi_handle_dr_smp_recv(is_switch, port_num, phys_port_cnt,
					&smp->hop_ptr, smp->hop_cnt,
					smp->route.dr.initial_path,
					smp->route.dr.return_path,
					opa_get_smp_direction(smp),
					smp->route.dr.dr_dlid ==
					OPA_LID_PERMISSIVE,
					smp->route.dr.dr_slid ==
					OPA_LID_PERMISSIVE);
}